// GLarena, a plugin based platform to teach OpenGL programming
// © Copyright 2012-2018, ViRVIG Research Group, UPC, https://www.virvig.eu
// 
// This file is part of GLarena
//
// GLarena is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "pluginLoader.h"
#include <QDir>
#include <QIODevice>
#include <QMenu>
#include <QProcess>
#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QPainter>
#include <QApplication>
#include <QRegularExpression>
#include <fstream>
#include <sstream>
#include <cmath>
#ifndef __APPLE__
  #include <GL/glu.h>
#else
  #include <glu.h>
#endif
#include <iostream>
#include <unistd.h>

PluginLoader::PluginLoader()
{
  pluginEnabled = false;
  pluginVersion = 0;
  filename = "";
  currentPlugin = -1; // no plugin being handled yet.
}

void PluginLoader::onPluginLoad()
{
  connect(&timer, SIGNAL(timeout()), glwidget(), SLOT(update()));
  timer.setInterval(16);
  timer.start();
  origCWD = QDir::currentPath();
  if (not QDir::setCurrent(glwidget()->getPluginPath()+"..")) {
    cerr << "Could not change CWD to " << (glwidget()->getPluginPath()+"..").toUtf8().data() << endl
         << "pluginLoader will not work correctly..." << endl;
  }
  // find qmake binary to use:
  QProcess *childP = new QProcess(this);
  QString program = "grep";
  QStringList arguments;
  arguments << "^QMAKE\\>"  << "Makefile";
  childP->start(program, arguments);
  if (not childP->waitForFinished()) {
    cerr << "Cannot extract the path for the qmake version used!" << endl <<
            "Exiting!..." << endl;
    QApplication::exit(-3);
  }
  QByteArray rslt = childP->readAll();
  int strt = rslt.indexOf("/");
  qmakePath = QString(rslt.right(rslt.size()-strt).chopped(1));

  // set grace period: the time (in msecs) to wait before recompiling.
#ifdef GRACETIME
  graceTime = GRACETIME;
#else
  graceTime = 0;
#endif
  char* tmp = getenv ("VGRACETIME");
  if (tmp!=0) graceTime=atoi(tmp);
  string::size_type gracepos =  args().find("--grace-time ");
  if (gracepos != string::npos) {
    gracepos += 13;
    gracepos += args().substr(gracepos).find_first_not_of(" ");
    graceTime = std::stol(args().substr(gracepos), nullptr, 0);
  }
  cerr << "initialized graceTime to " << graceTime << endl;
}

void PluginLoader::postFrame()
{
  checkForUpdates();
}

void PluginLoader::keyPressEvent(QKeyEvent*e)
{
  GLWidget &g =*glwidget();
  if (e->key() == Qt::Key_Space) showMenu(QCursor::pos());
  g.makeCurrent();

  /*
    if (e->key() == Qt::Key_S) 
    {
        QImage img = g.grabFramebuffer();
        QDateTime time = QDateTime::currentDateTime();
        QString name = QString("Snap-") + time.toString("yyyy-MM-dd----hh:mm:ss") + QString(".png");
        img.save(name);
        cout << "Image saved" << endl;
    }
    if (e->key() == Qt::Key_T) executeTest();
    if (e->key() == Qt::Key_C) compareTest();
  */
}


// TO DO
void PluginLoader::showMenu(const QPoint& pos)
{
  GLWidget& g = *glwidget();
  g.makeCurrent();
  
  timer.stop();

  // 1. Actions

  // Info
  vector<QAction*> info; 
  info.push_back(new QAction(QString("Current path: ") + QDir::currentPath() , glwidget()));
  if (filename!="")
    info.push_back(new QAction(filename  , glwidget()));
  else
    info.push_back(new QAction("No plugin attached", glwidget()));

  // Plugins 
  QAction* actionNewVSFS = new QAction("New plugin...", glwidget());
  connect(actionNewVSFS, SIGNAL(triggered()), this, SLOT(createDefaultPlugin()));

  QAction* actionCreateFromTemplate = new QAction("New (from existing plugin)...", glwidget());
  connect(actionCreateFromTemplate, SIGNAL(triggered()), this, SLOT(createPluginFromTemplate()));

  QAction* actionOpen = new QAction("Open plugin...", glwidget());
  connect(actionOpen, SIGNAL(triggered()), this, SLOT(attachPlugin()));

  //QAction* actionRun<Test = new QAction("Run test", glwidget());
  //connect(actionRunTest, SIGNAL(triggered()), this, SLOT(compareTest()));

  // Scene
  QAction* actionAddObject = new QAction("Add object...", glwidget());
  connect(actionAddObject, SIGNAL(triggered()), glwidget(), SLOT(addObject()));

  QAction* actionLoadObject = new QAction("Load object...", glwidget());
  connect(actionLoadObject, SIGNAL(triggered()), this, SLOT(loadObject()));

  QAction* actionClearScene = new QAction("Clear scene", glwidget());
  connect(actionClearScene, SIGNAL(triggered()), glwidget(), SLOT(clearScene()));

  // Camera
  QAction* actionResetCamera = new QAction("Reset camera", glwidget());
  connect(actionResetCamera, SIGNAL(triggered()), this, SLOT(resetCamera()));

  QAction* actionCameraPreset1 = new QAction("Preset 1", glwidget());
  connect(actionCameraPreset1, SIGNAL(triggered()), this, SLOT(cameraPreset1()));

  QAction* actionCameraPreset2 = new QAction("Preset 2", glwidget());
  connect(actionCameraPreset2, SIGNAL(triggered()), this, SLOT(cameraPreset2()));

  QAction* actionCameraPreset3 = new QAction("Preset 3", glwidget());
  connect(actionCameraPreset3, SIGNAL(triggered()), this, SLOT(cameraPreset3()));

  QAction* actionCameraPreset4 = new QAction("Preset 4", glwidget());
  connect(actionCameraPreset4, SIGNAL(triggered()), this, SLOT(cameraPreset4()));

  QAction* actionCameraPreset5 = new QAction("Preset 5", glwidget());
  connect(actionCameraPreset5, SIGNAL(triggered()), this, SLOT(cameraPreset5()));

  // Menu ----------------------
  QMenu menu(glwidget());

  QMenu* infos = menu.addMenu("Info");
  for (unsigned int i=0; i<info.size(); ++i)
    infos->addAction(info[i]);

  QMenu* plugs = menu.addMenu("Plugins");
  plugs->addAction(actionNewVSFS);
  plugs->addAction(actionOpen);
  plugs->addAction(actionCreateFromTemplate);
  plugs->addSeparator();
  plugs->addAction(actionOpen);
  //plugs->addSeparator();
  //plugs->addAction(actionRunTest);

  QMenu* scene = menu.addMenu("Scene");
  scene->addAction(actionClearScene);
  scene->addAction(actionLoadObject);
  scene->addAction(actionAddObject);

  QMenu* cameraMenu = menu.addMenu("Camera");
  cameraMenu->addAction(actionResetCamera);
  cameraMenu->addSeparator();
  cameraMenu->addAction(actionCameraPreset1);
  cameraMenu->addAction(actionCameraPreset2);
  cameraMenu->addAction(actionCameraPreset3);
  cameraMenu->addAction(actionCameraPreset4);
  cameraMenu->addAction(actionCameraPreset5);

  menu.exec(pos);
  g.makeCurrent();
   
  timer.start(); 
}

void PluginLoader::loadObject()
{
  glwidget()->clearScene();
  glwidget()->addObject();
}

void PluginLoader::loadObject(const QString& file)
{
  glwidget()->clearScene();
  glwidget()->addObjectFromFile(file);
}

void PluginLoader::resetCamera()
{
  camera()->init(scene()->boundingBox());
  glwidget()->update();
}

void PluginLoader::cameraPreset1()
{
  camera()->init(scene()->boundingBox());
  camera()->incrementAngleX(45);
  glwidget()->update();
}

void PluginLoader::cameraPreset2()
{
  camera()->init(scene()->boundingBox());
  camera()->incrementAngleX(45);
  camera()->incrementAngleY(45);
  glwidget()->update();
}

void PluginLoader::cameraPreset3()
{
  camera()->init(scene()->boundingBox());
  camera()->incrementAngleX(45);
  camera()->incrementAngleY(180);
  glwidget()->update();
}

void PluginLoader::cameraPreset4()
{
  camera()->init(scene()->boundingBox());
  camera()->incrementAngleX(45);
  camera()->incrementAngleY(45);
  camera()->incrementDistance(scene()->boundingBox().radius());
  camera()->updateClippingPlanes(scene()->boundingBox());
  glwidget()->update();
}
void PluginLoader::cameraPreset5()
{
  camera()->init(scene()->boundingBox());
  camera()->incrementAngleX(45);
  camera()->incrementAngleY(45);
  camera()->incrementDistance(10*scene()->boundingBox().radius());
  camera()->updateClippingPlanes(scene()->boundingBox());
  glwidget()->update();
}

void PluginLoader::reloadPlugin()
{
  QString title;
  glwidget()->makeCurrent();

  // clean-up
  //  glwidget()->resetPluginsToDefaults();
  if (currentPlugin >= 0) {
    glwidget()->unloadPlugin(currentPlugin);
    currentPlugin = -1;
  }
#ifndef __APPLE__
  QProcess::execute(QString("rm"), QProcess::splitCommand("-f "+glwidget()->getPluginPath()+"lib"+filename+QString::number(pluginVersion)+".so"));
#else
  QProcess::execute(QString("rm"), QProcess::splitCommand("-f "+glwidget()->getPluginPath()+"lib"+filename+QString::number(pluginVersion)+".dylib"));
#endif
  // compile new version
  ++pluginVersion;

  QFile filePRO(filename+"/"+filename+".pro");
  filePRO.open(QFile::WriteOnly | QFile::Truncate);
  QTextStream out(&filePRO);
  out << "TARGET     = $$qtLibraryTarget(" << filename << pluginVersion << ")" << "\n";
  out << "include(../common.pro)" << "\n";
  filePRO.close();

  QDir old = QDir::current();
  QDir::setCurrent(filename);
  cout << "about to execute " << qmakePath.toStdString() << endl; 
  int execRes = QProcess::execute(qmakePath);
  cout << "got execRes = " << execRes << endl;
  cout << "let's make it:" << endl;
  execRes = QProcess::execute("make", QProcess::splitCommand(QString("-j")));
  cout << "got execRes = " << execRes << endl;
  
  QStringList plugins;
#ifndef __APPLE__
  plugins << glwidget()->getPluginPath()+"lib"+filename+QString::number(pluginVersion)+".so";
#else
  plugins << glwidget()->getPluginPath()+"lib"+filename+QString::number(pluginVersion)+".dylib";
#endif
  currentPlugin = glwidget()->loadPlugins(plugins);

  QDir::setCurrent(old.path());

  QString name=filename;
  if (name=="") return;

  pluginEnabled = true; 
  
  if (QFile::exists(name+"/"+name+".h"))
    {
      QFileInfo fi(name+"/"+name+".h");
      title+=QString(fi.fileName());
      title+="   ";
      lastModifiedH = fi.lastModified();
    }
  else pluginEnabled = false;
    

  if (QFile::exists(name+"/"+name+".pro"))
    {
      QFileInfo fi(name+"/"+name+".pro");
      title+=QString(fi.fileName());
      title+="   ";
    }
  else pluginEnabled = false;

    
  if (QFile::exists(name+"/"+name+".cpp"))
    {
      QFileInfo fi(name+"/"+name+".cpp");
      title+=QString(fi.fileName());
      title+="   ";
      lastModifiedCPP = fi.lastModified();
    }
  else pluginEnabled = false;
    
  if (pluginEnabled)
    glwidget()->setWindowTitle(title);
  else 
    glwidget()->setWindowTitle("Some files are missing");
}


void PluginLoader::checkForUpdates()
{
  if (filename=="") return; 
  bool reload=false;
  QFileInfo infoH(filename+"/"+filename+".h");
  if (infoH.lastModified() > lastModifiedH and
      QDateTime::currentDateTime() > infoH.lastModified().addMSecs(graceTime)) reload=true;
    
  QFileInfo infoCPP(filename+"/"+filename+".cpp");
  if (infoCPP.lastModified() > lastModifiedCPP and
      QDateTime::currentDateTime() > infoCPP.lastModified().addMSecs(graceTime)) reload=true;
    
  if (reload) reloadPlugin();
}

void PluginLoader::attachPlugin()
{
  QString name = QFileDialog::getOpenFileName(glwidget(),
					      tr("Open Plugin"), QDir::currentPath(), tr("Plugin Files (*.cpp *.pro)"));
  if (name!="") 
    {
      name.chop(4);
      attachPlugin(QDir(name).dirName());
    }
}

void PluginLoader::attachPlugin(QString name)
{
  filename = name;
  pluginVersion = 0;
  reloadPlugin();
  openFilesInTextEditor();
}

void PluginLoader::openFilesInTextEditor()
{
#ifndef __APPLE__
  QString editor = "gedit";
#else
  QString editor = "/Applications/TextEdit.app";
#endif
  char* pPath = getenv ("VEDITOR");
  if (pPath!=NULL)
    editor=QString(pPath);

  QProcess* process = new QProcess(glwidget());

#ifndef __APPLE__
  //process->startDetached(editor, QStringList() << filename+"/"+filename+".h" << filename+"/"+filename+".cpp" << filename+"/"+filename+".pro");
  process->startDetached(editor, QStringList() << filename+"/"+filename+".h" << filename+"/"+filename+".cpp");
#else
  process->startDetached("open", QStringList() << QString("-a")+editor << filename+"/"+filename+".h" << filename+"/"+filename+".cpp" << filename+"/"+filename+".cpp");
#endif

}


void PluginLoader::createDefaultPlugin()
{
  bool ok;
  QString _filename;
  do {
    _filename = QInputDialog::getText(glwidget(), "New plugin",
				     "Filename:", QLineEdit::Normal,
				     "myPlugin", &ok);
    if (_filename.contains(QRegularExpression("[^a-zA-Z0-9_]"))) {
      QMessageBox::warning(glwidget(), tr("PluginLoader"),
				     tr("Invalid plugin name. \n"
					"The name should consist of only alphanumerical "
					"characters and underscores, without spaces or "
					"other symbols."),
				     QMessageBox::Ok, QMessageBox::Ok); 
    }
    
  } while (_filename.contains(QRegularExpression("[^a-zA-Z0-9_]")));

  if (!ok || _filename.isEmpty()) return;
  
  // check if files already exist
  if (QFile::exists(_filename+"/"+_filename+".h") || QFile::exists(_filename+"/"+_filename+".pro") || QFile::exists(_filename+"/"+_filename+".cpp") )
    {
      int ret = QMessageBox::warning(glwidget(), tr("PluginLoader"),
				     tr("One or more files already exist. \n"
					"These files will be overwriten with default content."),
				     QMessageBox::Ok | QMessageBox::Cancel,
				     QMessageBox::Ok);

      if (ret!=QMessageBox::Ok) return;
    }

  filename = _filename;
  QDir().mkdir(filename);

  // Check if files can be opened
  QFile fileH(filename+"/"+filename+".h");
  if (!fileH.open(QFile::WriteOnly | QFile::Truncate)) 
    {
      cout << "Cannot open .h file for writing" << "\n";
      return;
    }

  QFile filePRO(filename+"/"+filename+".pro");
  if (!filePRO.open(QFile::WriteOnly | QFile::Truncate)) 
    {
      fileH.close();
      return;
    }
    
  QFile fileCPP(filename+"/"+filename+".cpp");
  if (!fileCPP.open(QFile::WriteOnly | QFile::Truncate)) 
    {
      fileH.close();
      filePRO.close();
      return;
    }

  QString className = QString(filename[0]).toUpper() + QString(filename.right(filename.size()-1));

  // Write .H
  if (true)
    {
      QTextStream out(&fileH);

      out << "#ifndef _" << filename.toUpper() << "_H" << "\n";
      out << "#define _" << filename.toUpper() << "_H" << "\n";
      out << "\n";

      out << "#include \"plugin.h\" " << "\n" << "\n";

		
      out << "class " << className << ": public QObject, public Plugin" << "\n";

      out << "{" << "\n";
      out << "\tQ_OBJECT" << "\n";
      out << "\tQ_PLUGIN_METADATA(IID \"Plugin\") " << "\n";   
      out << "\tQ_INTERFACES(Plugin)" << "\n" << "\n";
      out << "  public:" << "\n";
      out << "\t void onPluginLoad();" << "\n";
      out << "\t void preFrame();" << "\n";
      out << "\t void postFrame();" << "\n";
      out << "\n";
      out << "\t void onObjectAdd();" << "\n";
      out << "\t bool drawScene();" << "\n";
      out << "\t bool drawObject(int);" << "\n";
      out << "\n";
      out << "\t bool paintGL();" << "\n";
      out << "\n";
      out << "\t void keyPressEvent(QKeyEvent *);" << "\n";
      out << "\t void mouseMoveEvent(QMouseEvent *);" << "\n";
      out << "  private:" << "\n";
      out << "\t// add private methods and attributes here" << "\n";
      out << "};" << "\n" << "\n";
      out << "#endif" << "\n";
  
      fileH.close();
    }
  // Write .PRO
  if (true)
    {
      QTextStream out(&filePRO);
      out << "TARGET     = $$qtLibraryTarget(" << filename << QString::number(pluginVersion) << ")" << "\n";
      out << "include(../common.pro)" << "\n";
      filePRO.close();
    }
  // Write .CPP
  if (true)
    {   
      QTextStream out(&fileCPP);
       
      out << "#include \"" << filename << ".h\"" << "\n";
      out << "#include \"glwidget.h\"" << "\n" << "\n";

      out << "void " << className << "::onPluginLoad()" << "\n";
      out << "{" << "\n";
      out << "\t" << "\n";
      out << "}" << "\n" << "\n";

      out << "void " << className << "::preFrame()" << "\n";
      out << "{" << "\n";
      out << "\t" << "\n";
      out << "}" << "\n" << "\n";

      out << "void " << className << "::postFrame()" << "\n";
      out << "{" << "\n";
      out << "\t" << "\n";
      out << "}" << "\n" << "\n";

      out << "void " << className << "::onObjectAdd()" << "\n";
      out << "{" << "\n";
      out << "\t" << "\n";
      out << "}" << "\n" << "\n";

      out << "bool " << className << "::drawScene()" << "\n";
      out << "{" << "\n";
      out << "\treturn false; // return true only if implemented" << "\n";
      out << "}" << "\n" << "\n";

      out << "bool " << className << "::drawObject(int)" << "\n";
      out << "{" << "\n";
      out << "\treturn false; // return true only if implemented" << "\n";
      out << "}" << "\n" << "\n";

      out << "bool " << className << "::paintGL()" << "\n";
      out << "{" << "\n";
      out << "\treturn false; // return true only if implemented" << "\n";
      out << "}" << "\n" << "\n";

      out << "void " << className << "::keyPressEvent(QKeyEvent *)" << "\n";
      out << "{" << "\n";
      out << "\t" << "\n";
      out << "}" << "\n" << "\n";

      out << "void " << className << "::mouseMoveEvent(QMouseEvent *)" << "\n";
      out << "{" << "\n";
      out << "\t" << "\n";
      out << "}" << "\n" << "\n";

      fileCPP.close();
    }

  pluginEnabled = true;
  attachPlugin(filename);
}
 
void replace(QString filename, QString old, QString news)
{
	
  QFile file(filename);
  file.open(QIODevice::ReadWrite); 
  QByteArray fileData = file.readAll(); 
  QString text(fileData); 
  text.replace(old, news); // replace text in string
  file.seek(0); // go to the beginning of the file
  file.write(text.toUtf8()); // write the new text back to the file
  file.close();
}


void PluginLoader::createPluginFromTemplate() 
{

  // template name
  QString name = QFileDialog::getOpenFileName(glwidget(),
					      tr("Open Plugin"), QDir::currentPath(), tr("Plugin Files (*.pro *.cpp )"));
  if (name=="") return;
  name.chop(4);
  name = QDir(name).dirName();
  cout << name.toStdString() << endl;

  bool ok;
  QString _filename;
  do {
    _filename = QInputDialog::getText(glwidget(), "New Plugin",
				     "Base filename:", QLineEdit::Normal,
				     "myNewPlugin", &ok);
     if (_filename.contains(QRegularExpression("[^a-zA-Z0-9_]"))) {
      QMessageBox::warning(glwidget(), tr("PluginLoader"),
				     tr("Invalid plugin name. \n"
					"The name should consist of only alphanumerical "
					"characters and underscores, without spaces or "
					"other symbols."),
				     QMessageBox::Ok, QMessageBox::Ok); 
     }
  } while (_filename.contains(QRegularExpression("[^a-zA-Z0-9_]")));   

  if (!ok || _filename.isEmpty()) return;
  
  // check if files already exist
  if (QFile::exists(_filename+"/"+_filename+".h") || QFile::exists(_filename+"/"+_filename+".cpp") )
    {
      int ret = QMessageBox::warning(glwidget(), tr("PluginLoader"),
				     tr("One or more files already exist. \n"
					"These files will be overwriten with default content."),
				     QMessageBox::Ok | QMessageBox::Cancel,
				     QMessageBox::Ok);

      if (ret!=QMessageBox::Ok) return;
    }
  
  filename = _filename;
  pluginEnabled = true;
  QDir().mkdir(filename);

  QString classNameOld = QString(name[0]).toUpper() + QString(name.right(name.size()-1));
  QString classNameNew = QString(filename[0]).toUpper() + QString(filename.right(filename.size()-1));

  if (QFile::exists(name+"/"+name+".h")) 
    {
      QFile::copy(name+"/"+name+".h", filename+"/"+filename+".h");
      replace(filename+"/"+filename+".h", classNameOld, classNameNew);
      replace(filename+"/"+filename+".h", classNameOld.toUpper(),
	                                  classNameNew.toUpper());
    }
  else
    pluginEnabled = false;

  if (QFile::exists(name+"/"+name+".pro")) 
    {
      QFile::copy(name+"/"+name+".pro", filename+"/"+filename+".pro");
      replace(filename+"/"+filename+".pro", name, filename);
		
    }
  else
    pluginEnabled = false;

  if (QFile::exists(name+"/"+name+".cpp")) 
    {
      QFile::copy(name+"/"+name+".cpp", filename+"/"+filename+".cpp");
      replace(filename+"/"+filename+".cpp", name, filename);
      replace(filename+"/"+filename+".cpp", classNameOld, classNameNew);
    }
  else
    pluginEnabled = false;

  if (pluginEnabled)
    attachPlugin(filename);
  else
    cout << "Error copying files" << endl;

}




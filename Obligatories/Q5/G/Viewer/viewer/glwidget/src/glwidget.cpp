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

#define _USE_MATH_DEFINES 1
#include <cmath>
#include "glwidget.h"
#include <QMatrix4x4>
#ifndef __APPLE__
  #include <GL/glu.h>
#else
  #include <glu.h>
#endif
#include <QPluginLoader>
#include <QCoreApplication>
#include "plugin.h"
#include <QOpenGLShaderProgram>
#include <QApplication>
#include <fstream>
#include <unistd.h>

const float MIN_AXES_LENGTH = 0.1;

GLWidget::GLWidget(const string& args):
  gradingPlugin(false), defaultsLoaded(false), drawPlugin(0)
{
    mainArgs = args;
    setFocusPolicy(Qt::ClickFocus);  // per rebre events de teclat
    string::size_type gradepos =  args.find("--grade-shader ");
    grading = gradepos != string::npos;
    string::size_type gradepluginpos =  args.find("--grade-plugin ");
    if (gradepluginpos != string::npos) {
      gradingPlugin = true;
      grading = true;                // no interaction if in grading mode
      gradepluginpos += args.substr(gradepluginpos+15).find_first_not_of(" ");
      int nameLength = args.substr(gradepluginpos+15).find_first_of(" .");
      pluginToGrade = args.substr(gradepluginpos+15, nameLength);
      std::cout << "Detected flag to grade plugin `" << pluginToGrade << "'"
		<< std::endl;
    }
}

void GLWidget::setPluginPath(const QString & p) {
  pluginPath = p;
}

const QString& GLWidget::getPluginPath() const {
  return pluginPath;
}


void GLWidget::initializeGL()
{   
    // glewExperimental = GL_TRUE;
    // glewInit(); // necessari per cridar funcions de les darreres versions d'OpenGL
    initializeOpenGLFunctions();
    glGetError();  // Reinicia la variable d'error d'OpenGL

    glClearColor(0.8f, 0.8f, 1.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    // Report GL version obtained
    //std::cout << glGetString(GL_VERSION) << std::endl;
    //std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    // unlit shader
    QOpenGLShader vs(QOpenGLShader::Vertex);
    vs.compileSourceCode("#version 330 core \n layout (location = 0) in vec3 vertex; layout (location = 1) in vec3 normal; uniform mat4 modelViewProjectionMatrix; out vec4 frontColor;    void main() { frontColor = vec4(abs(normal),0.25); gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0); }");
    QOpenGLShader fs(QOpenGLShader::Fragment);
    fs.compileSourceCode("#version 330 core \n in vec4 frontColor; out vec4 FragColor; void main() {FragColor = frontColor;}");	
    unlitProgram.addShader(&vs);
    unlitProgram.addShader(&fs);
    unlitProgram.link();
/*
qDebug() << vs.log() << endl;
qDebug() << vs.isCompiled() << endl;

qDebug() << fs.log() << endl;
qDebug() << fs.isCompiled() << endl;

    qDebug() << unlitProgram.log() << endl;
qDebug() << unlitProgram.isLinked() << endl;
*/
}

QOpenGLShaderProgram* GLWidget::defaultProgram()
{
    return &unlitProgram; 
}


void GLWidget::loadDefaultPlugins(QString& plugins) {
    QStringList defaultPlugins;

    if (plugins.size()>0) // use user-provided plugin list 
    {
        defaultPlugins = plugins.split(";");
        for (int i=0; i<defaultPlugins.size(); ++i)
        {
            defaultPlugins[i]=pluginPath+defaultPlugins[i];
        }               
    }
    else
    {
        #if defined(__APPLE__)
        defaultPlugins << pluginPath+"libdrawvbong.dylib";
        defaultPlugins << pluginPath+"librenderdefault.dylib";
        defaultPlugins << pluginPath+"libnavigatedefault.dylib";
        #elif defined(__unix__)
        //defaultPlugins << pluginPath+"libdrawimmediate.so";
        defaultPlugins << pluginPath+"libdrawvbong.so";
        //defaultPlugins << pluginPath+"libshaderloader.so";
        defaultPlugins << pluginPath+"librenderdefault.so";
        defaultPlugins << pluginPath+"libnavigatedefault.so";
        #else  // Windows?
        defaultPlugins << pluginPath+"libdrawvbong.dll";
        defaultPlugins << pluginPath+"librenderdefault.dll";
        defaultPlugins << pluginPath+"libnavigatedefault.dll";
        #endif
    }
    loadPlugins(defaultPlugins);
    defaultsLoaded = true;
}

void GLWidget::resetPluginsToDefaults() {
  for (unsigned int i=0; i<plugins.size(); ++i) {
    std::cout << "Unloading " << plugins[i]->fileName().toStdString() << std::endl;
    plugins[i]->unload();
    delete plugins[i];
  }
  plugins.clear();
  QString tmp = QString(getenv ("VPLUGINS"));
  loadDefaultPlugins(tmp);
}

void GLWidget::unloadPlugin(int i) {
  if (i<0 or unsigned(i)>=plugins.size()) return;
  std::cout << "Unloading " << plugins[i]->fileName().toStdString() << std::endl; 
  plugins[i]->unload();
  delete plugins[i];
  plugins.erase(plugins.begin()+i);
}

Scene* GLWidget::scene()
{
    return &pscene;
}

Camera* GLWidget::camera()
{
    return &pcamera;
}


#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << endl;

int printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
			     file, line, gluErrorString(glErr), func);
        retCode = 1;
    }
    return retCode;
}


void GLWidget::drawAxes() 
{
    float L = 1;

    static bool created = false;
    static QOpenGLShaderProgram program;
    static GLuint VAO_axes;

    if (!created)
    {
        created = true;
        // 1. Create shaders

        // VS 
        QOpenGLShader vs(QOpenGLShader::Vertex);
        vs.compileSourceCode("#version 330 core \n in vec3 vertex; in vec3 color; uniform mat4 modelViewProjectionMatrix; out vec4 frontColor;    void main() { frontColor = vec4(color,1); gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0); }");

        // FS    
        QOpenGLShader fs(QOpenGLShader::Fragment);
        fs.compileSourceCode("#version 330 core \n in vec4 frontColor; out vec4 FragColor; void main() {FragColor = frontColor;}");	

        // Program
        program.addShader(&vs);
        program.addShader(&fs);
        program.link();

        // Get location of VS attributes
        GLuint vertexLoc = program.attributeLocation("vertex");
        GLuint colorLoc  = program.attributeLocation("color");

        // 2. Create VBO Buffers

        // Create & bind empty VAO
        glGenVertexArrays(1, &VAO_axes);
        glBindVertexArray(VAO_axes);


        // Create VBO with (x,y,z) coordinates
        
        float coords[] = { 0, 0, 0, 
                           L, 0, 0, 
                           0, 0, 0, 
                           0, L, 0,
                           0, 0, 0,
                           0, 0, L};

        GLuint VBO_coords;
        glGenBuffers(1, &VBO_coords);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(vertexLoc);

        // Create VBO with (r,g,b) color
        float colors[] = {1, 0, 0, 1, 0, 0, 
                          0, 1, 0, 0, 1, 0,
                          0, 0, 1, 0, 0, 1};
        GLuint VBO_colors;
        glGenBuffers(1, &VBO_colors);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
        glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(colorLoc);

        glBindVertexArray(0);


    }

    program.bind();

    // 1. Define uniforms 
    float r = max(MIN_AXES_LENGTH, scene()->boundingBox().radius());
    QMatrix4x4 scale;
    scale.scale(r,r,r);
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix()*scale;
    program.setUniformValue("modelViewProjectionMatrix", MVP);    

    // 2. Draw
    glBindVertexArray (VAO_axes);
    glDrawArrays(GL_LINES, 0, 6);
    glBindVertexArray(0);

    program.release();

    // 5. CleanUp
    /*
    glDeleteVertexArrays(1, &VAO_axes);
    glDeleteBuffers(1, &VBO_coords);
    glDeleteBuffers(1, &VBO_colors);
    */
    
/* 
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(L,0,0); // X
    glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,L,0); // Y
    glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,L); // Z
    glEnd();
    glEnable(GL_LIGHTING);
   */ 

}


void GLWidget::drawPoint(const Vector& pos, float r, float g, float b) 
{
    static bool created = false;
    static QOpenGLShaderProgram program;
    static GLuint VAO;

    if (!created)
    {
        created = true;
        // 1. Create shaders
        QOpenGLShader vs(QOpenGLShader::Vertex);
        vs.compileSourceCode("#version 330 core \n in vec3 vertex; in vec3 color; uniform mat4 modelViewProjectionMatrix; out vec4 frontColor;    void main() { frontColor = vec4(color,1); gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0); }");
        QOpenGLShader fs(QOpenGLShader::Fragment);
        fs.compileSourceCode("#version 330 core \n in vec4 frontColor; out vec4 FragColor; void main() {FragColor = frontColor;}");	
        program.addShader(&vs);
        program.addShader(&fs);
        program.link();

        // Get location of VS attributes
        GLuint vertexLoc = program.attributeLocation("vertex");
        GLuint colorLoc  = program.attributeLocation("color");

        // 2. Create VBO Buffers

        // Create & bind empty VAO
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        // Create VBO with (x,y,z) coordinates
        float coords[] = { 0, 0, 0}; 
        GLuint VBO_coords;
        glGenBuffers(1, &VBO_coords);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(vertexLoc);
        // Create VBO with (r,g,b) color
        float colors[] = {r, g, b};
        GLuint VBO_colors;
        glGenBuffers(1, &VBO_colors);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
        glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(colorLoc);

        glBindVertexArray(0);
    }

    program.bind();

    // 1. Define uniforms
    QMatrix4x4 T;
    T.translate(pos); 
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix()*T;
    program.setUniformValue("modelViewProjectionMatrix", MVP);    

    // 2. Draw
    glPointSize(8);
    glBindVertexArray (VAO);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
    program.release();
}

Box GLWidget::boundingBoxIncludingAxes() 
{
    float L = max(MIN_AXES_LENGTH, scene()->boundingBox().radius());
    Box box(Point(0,0,0), Point(L,L,L)); // AABB dels eixos
    if (pscene.objects().size())
        box.expand(pscene.boundingBox());
    return box;
}

void GLWidget::resetCamera()
{
    pcamera.init(scene()->boundingBox()); //IncludingAxes());
    pcamera.updateClippingPlanes(boundingBoxIncludingAxes());

    update();
}

void GLWidget::paintGL( void )
{
  static int pass=0;

    //qDebug() << unlitProgram.log() << endl;
    //qDebug() << unlitProgram.isLinked() << endl;

    unlitProgram.bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    unlitProgram.setUniformValue("modelViewProjectionMatrix", MVP);    


    //cout << "PaintGL" << endl;
    glEnable(GL_DEPTH_TEST);
    for (unsigned int i=0; i<plugins.size(); ++i)
        qobject_cast<Plugin*>(plugins[i]->instance())->preFrame();
    
    // call to paintGL() until one returns true
    for (int i=int(plugins.size())-1; i>=0; --i) // notice reverse order
        if (qobject_cast<Plugin*>(plugins[i]->instance())->paintGL()) break;

    for (unsigned int i=0; i<plugins.size(); ++i) 
        qobject_cast<Plugin*>(plugins[i]->instance())->postFrame();

    //cout << "endPaintGL" << endl;

    unlitProgram.release();
    if (gradingPlugin and defaultsLoaded) {
      gradingPlugin = false;
      std::cout << "#-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
      cout << "Pass: " << pass++ << endl;
      executeTest(); 
      std::cout << "#-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
      exit(0);
    }
}

void GLWidget::executeTest() {
  QString testFilename = QString(pluginToGrade.c_str())+".test";
  if (!QFile::exists(testFilename)) {
    QString tests = "/assig/grau-g/tests";
    char* tmp = getenv ("VTESTS");
    if (tmp!=NULL) tests=QString(tmp);
    testFilename = tests + QString("/")+ pluginToGrade.c_str() + ".test";
    if (!QFile::exists(testFilename)) {
      cerr << "Cannot find test file:" << (testFilename).toStdString() << endl;
      return;
    }
  }
  ifstream f((testFilename).toStdString().c_str());
  if (!f.is_open()) {
    cerr << "Cannot open test file " << (testFilename).toStdString() << endl;
    
    return;
  }
  cout << "Running tests in " <<  (testFilename).toStdString() << std::endl;
  while (!f.eof()) {
    string cmd;
    string s;
    f >> cmd;
    if (cmd=="clearScene") {
      clearScene();
    } else if  (cmd=="resize") {
      int w, h;
      f >> w >> h;
      resize(w,h);
    } else if (cmd=="loadObject") {
      f >> s;
      if (!QFile::exists(QString(s.c_str())))
	{
	  QString models = "/assig/grau-g/models";
	  char* tmp = getenv ("VMODELS");
	  if (tmp!=NULL) models=QString(tmp);
	  //cout << "No he pogut obrir " << s << std::endl;
	  s = (models+QString("/")+QFileInfo(s.c_str()).fileName()).toStdString();
	  //std::cout<<"així que provo amb: " <<s<<std::endl;
	}
      clearScene();
      addObjectFromFile(QString(s.c_str()));      
    } else if (cmd=="addObject") {
      f >> s;
      if (!QFile::exists(QString(s.c_str())))
	{
	  QString models = "/assig/grau-g/models";
	  char* tmp = getenv ("VMODELS");
	  if (tmp!=NULL) models=QString(tmp);
	  //cout << "No he pogut obrir " << s << std::endl;
	  s = (models+QString("/")+QFileInfo(s.c_str()).fileName()).toStdString();
	  //std::cout<<"així que provo amb: " <<s<<std::endl;
	}
      addObjectFromFile(QString(s.c_str()));      
    } else if (cmd=="resetCamera") {
      camera()->init(scene()->boundingBox());
    } else if (cmd=="dist") {
      float dist;
      f >> dist;
      camera()->setDistance(dist*scene()->boundingBox().radius());
      camera()->updateClippingPlanes(scene()->boundingBox());
    } else if (cmd=="pitch") {
      float angle;
      f >> angle;
      camera()->setAngleX(angle);
    } else if (cmd=="yaw") {
      float angle;
      f >> angle;
      camera()->setAngleY(angle);
    } else if (cmd=="roll") {
      float angle;
      f >> angle;
      camera()->setAngleZ(angle);
    } else if (cmd=="preset1") {
      // cameraPreset1();  (better move the routines here?
      camera()->init(scene()->boundingBox());
      camera()->incrementAngleX(45);
      update();
    } else if (cmd=="preset2") {
      // cameraPreset2();
      camera()->init(scene()->boundingBox());
      camera()->incrementAngleX(45);
      camera()->incrementAngleY(45);
      update();
    } else if (cmd=="preset3") {
      //cameraPreset3();
      camera()->init(scene()->boundingBox());
      camera()->incrementAngleX(45);
      camera()->incrementAngleY(180);
      update();
    } else if (cmd=="preset4") {
      //cameraPreset4();
      camera()->init(scene()->boundingBox());
      camera()->incrementAngleX(45);
      camera()->incrementAngleY(45);
      camera()->incrementDistance(scene()->boundingBox().radius());
      camera()->updateClippingPlanes(scene()->boundingBox());
      update();
    } else if (cmd=="preset5") {
      //cameraPreset5();
      camera()->init(scene()->boundingBox());
      camera()->incrementAngleX(45);
      camera()->incrementAngleY(45);
      camera()->incrementDistance(10*scene()->boundingBox().radius());
      camera()->updateClippingPlanes(scene()->boundingBox());
      update();
    } else if (cmd=="grab") {
      f >> s;
      // -------------------------------------------------------------
      // Now here comes an UGLY hack; withot some resizing, Qt's
      // grabFramebuffer() fails! Then the following two lines are
      // better than forcing all .test files to do a resize (albeit
      // most will). Two are needed because a resize to current size
      // does nothing...
      resize(width()-1, height());
      resize(width()+1, height());
      // END UGLY hack
      // -------------------------------------------------------------
      // update(); We do not need this guy while we have the UGLY hack
      QImage img = grabFramebuffer();
#ifdef __Apple__
      if (img.size() != size()) { // seems we're in a machine w. retina display
	img = img.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
      }
#endif      
      QString name = pluginToGrade.c_str() + QString("-out") + s.c_str() + QString(".png");
      img.save(name);
    } else if (cmd=="exit") {
      QApplication::quit();
    } else if (cmd=="addPlugin") {
      f >> s;
      loadPlugins(QStringList(s.c_str()));
    } else if (cmd=="sleep") {
      // no podem controlar exactament el 'uniform time' en els plugins,
      // però podem "mostrejar" en el temps per validar
      useconds_t milis;
      f >> milis;
      usleep(milis*1000);
    } else if (QString(cmd.c_str()).trimmed()!="")
      cout << "Unrecognized command: " << cmd << endl;
  }
  f.close();
}

void GLWidget::resizeGL (int width, int height)
{
    glViewport (0, 0, width, height);
    pcamera.setAspectRatio( (float)width/(float)height);
}

void GLWidget::loadPlugin()
{
    QStringList list = QFileDialog::getOpenFileNames(NULL, "Select one or more plugins to open", pluginPath, "Plugins (*.dll *.so *.dylib)");
    loadPlugins(list);
}

// returns position of last plugin loaded, or -1 if none.
int GLWidget::loadPlugins(const QStringList& list) {
    QStringList::ConstIterator it = list.constBegin();
    int res = -1;
    while(it != list.constEnd()) 
    {
        QString name = *it;
        QPluginLoader *loader = new QPluginLoader(name);
        if (! loader->load()) {
        	  qDebug() << "Could not load plugin " << name << "\n";
                qDebug() << loader->errorString() << "\n";

	        }
        if (loader->isLoaded()) 
        {
            qDebug() << "Loaded plugin: " << loader->fileName(); // << 	endl;
            QObject *plugin = loader->instance();
            if (plugin) 
            {
                plugins.push_back(loader);
		res = plugins.size()-1;
                Plugin *plugin = qobject_cast<Plugin *>(loader->instance());
                // initialize plugin
                if (plugin)
                {
                    plugin->setWidget(this);
                    plugin->setArgs(mainArgs);
                    plugin->onPluginLoad();
                    if (plugin->drawScene()) {// overrides drawScene?
                        drawPlugin = plugin;
		    }
                }
            }
        }
        else 
        {
	  qDebug() << "Load error: " << name << "\n";
	        delete loader;
        }
        
        ++it;
    }

    // make sure all plugins know about the latest plugin that overrides drawScene
    for (unsigned int i=0; i<plugins.size(); ++i)
    {
        Plugin *plugin = qobject_cast<Plugin *>(plugins[i]->instance());
        if (plugin)
            plugin->setDrawPlugin(drawPlugin);
        else
        {
            qDebug() << "Error: the plugin must implement the Plugin interface" << "\n" <<
            " Example: " << "\n" << 
            "   Q_INTERFACES(Plugin)" << "\n";
        }
    }

    resetCamera();
    return res;
}

void GLWidget::help( void ){
    cout<<"Tecles definides: \n";
    cout<<"a         Afegeix plugins\n";
    cout<<"l         Afegeix un objecte\n";
    cout<<"f         Pinta en filferros\n";
    cout<<"s         Pinta amb omplert de polígons\n";
    cout<<"h,H       Imprimir aquesta ajuda\n";
}

void GLWidget::showPlugins() const
{
    qDebug() << "Current list of plugins: ";
    for (unsigned int i=0; i<plugins.size(); ++i)
        qDebug() << plugins[i]->fileName() << "\n";
}

void GLWidget::keyPressEvent(QKeyEvent *e)
{
  if (grading) return;
    //cout << "keyPressEvent" << endl;
  Vector angles;
    switch( e->key() ) 
    {	    
    case Qt::Key_A: 
        loadPlugin();
        update();
        break;

    case Qt::Key_D:
        showPlugins();
	    break;

    case Qt::Key_U:
        resetPluginsToDefaults();
	    update();
	break;

    case Qt::Key_L: 
        addObject();
        break;        
        
    case Qt::Key_F: 
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        update();
        break;

    case Qt::Key_S: 
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        update();
        break;

    case Qt::Key_H:
        help();
        break;

    case Qt::Key_Q:  // Dump camera in a way usable in a .test
      angles = camera()->eulerAngles();
      std::cout << "--------------Current Camera-------------------"
                << std::endl;
      std::cout << "pitch " << angles[0] << std::endl;
      std::cout << "yaw   " << angles[1] << std::endl;
      std::cout << "roll  " << angles[2] << std::endl;
      std::cout << "dist  "
                << camera()->getDist()/scene()->boundingBox().radius()
                << std::endl;
      std::cout << "--------------  end   dump  -------------------"
                << std::endl;
      break;
      
    case Qt::Key_Escape: 
      QCoreApplication::exit(0);
      break;
        
    default: 
        e->ignore(); // el propaguem cap al pare...
    }
    
    for (unsigned int i=0; i<plugins.size(); ++i) 
        qobject_cast<Plugin*>(plugins[i]->instance())->keyPressEvent(e);

    //cout << "endkeyPressEvent" << endl;
}


void GLWidget::mousePressEvent( QMouseEvent *e)
{
  if (grading) return;
  for (unsigned int i=0; i<plugins.size(); ++i) 
    qobject_cast<Plugin*>(plugins[i]->instance())->mousePressEvent(e);
}

void GLWidget::mouseReleaseEvent( QMouseEvent *e)
{
  if (grading) return;
  for (unsigned int i=0; i<plugins.size(); ++i) 
    qobject_cast<Plugin*>(plugins[i]->instance())->mouseReleaseEvent(e);
}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{ 
  if (grading) return;
  for (unsigned int i=0; i<plugins.size(); ++i) 
    qobject_cast<Plugin*>(plugins[i]->instance())->mouseMoveEvent(e);
}

void	 GLWidget::keyReleaseEvent ( QKeyEvent * e)
{
  if (grading) return;
  for (unsigned int i=0; i<plugins.size(); ++i) 
    qobject_cast<Plugin*>(plugins[i]->instance())->keyReleaseEvent(e);
}
 
void	 GLWidget::wheelEvent ( QWheelEvent *e)
{
  if (grading) return;
  for (unsigned int i=0; i<plugins.size(); ++i) 
    qobject_cast<Plugin*>(plugins[i]->instance())->wheelEvent(e);
}

void GLWidget::clearScene()
{
  makeCurrent();
    pscene.clear();

    // propagate to all plugins
    for (unsigned int i=0; i<plugins.size(); ++i) 
      qobject_cast<Plugin*>(plugins[i]->instance())->onSceneClear();

    resetCamera();
}

void GLWidget::addObjectFromFile(const QString& filename)
{
  makeCurrent();
    std::string name = filename.toLocal8Bit().constData();
    Object o(name.c_str());
    o.readObj(name.c_str());
    pscene.addObject(o);
    
    // propagate to all plugins
    for (unsigned int i=0; i<plugins.size(); ++i) 
      qobject_cast<Plugin*>(plugins[i]->instance())->onObjectAdd();
    
    resetCamera();

    QFileInfo fi(filename);
    cout << "Added object: " << fi.fileName().toStdString() << " (" << name << ")" << endl;

}

void GLWidget::addObject()
{
    QString models = "/assig/grau-g/models";
    char* tmp = getenv ("VMODELS");
    if (tmp!=NULL) models=QString(tmp);

    QStringList files = QFileDialog::getOpenFileNames(NULL, "Select one or more models to open", models, "Models (*.obj)");
    QStringList::Iterator it = files.begin();
    while(it != files.end()) 
    {
        QString    fileName = (*it);
        addObjectFromFile(fileName);
        ++it;
    }

    //resetCamera();
}


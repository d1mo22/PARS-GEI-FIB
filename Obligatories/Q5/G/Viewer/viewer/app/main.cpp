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

#include <QApplication>
#include "glwidget.h"
#include <string>
using namespace std;

int main(int argc, char ** argv)
{
    // Used to pass command line args to the plugins
    string args;
    bool setVersion = true;
    for (int i=1; i<argc; ++i) {
      if (not strcmp(argv[i], "--no-set-version")){
	  setVersion = false;
	} else {
	  args+=argv[i];
	  args+=" ";
	}
    }
    QSurfaceFormat glFormat;
    if (setVersion) {
      // Specify an OpenGL 3.3 format using the appropriate profile.
      glFormat.setVersion( 3, 3);  // Should not be needed... In fact,
                                   // breaks show-help-ng!!
      char* tmp = getenv ("VPROFILE");
      glFormat.setProfile(QSurfaceFormat::CoreProfile); 
      if (tmp!=NULL) 
	{
	  if (QString(tmp)!=QString("CORE"))
            glFormat.setProfile( QSurfaceFormat::CompatibilityProfile ); 
	}
    }
    QSurfaceFormat::setDefaultFormat(glFormat);
    QApplication a(argc, argv);
    // Create OpenGL window
    GLWidget glWidget(args);
    glWidget.show();

    // Print OpenGL version and profile 
    QSurfaceFormat f = glWidget.format();
    cout << "OpenGL Version: " << f.majorVersion() << "." << f.minorVersion() << endl;
    cout << "OpenGL Profile: " << ((f.profile()==QSurfaceFormat::CoreProfile)?"Core":"Compatibility") << endl;

    // Plugin path
    QString pluginPath;
    char *tmp = getenv ("VPLUGINPATH");
    if (tmp!=NULL) pluginPath=QString(tmp);
    else
    {
        pluginPath = a.applicationDirPath();
        #if defined(__APPLE__)
        pluginPath.append("/../../../");
        #else
        pluginPath.append("/");
        # endif
        pluginPath.append("../../plugins/bin/");
    }
    glWidget.setPluginPath(pluginPath);

    // Load default plugins
    QString plugins = QString(getenv ("VPLUGINS"));
    glWidget.loadDefaultPlugins(plugins);

    // Load default object
    QString models = "/assig/grau-g/models";
    tmp = getenv ("VMODELS");
    if (tmp!=NULL) models=QString(tmp);
    glWidget.addObjectFromFile(models + "/default.obj");

    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}



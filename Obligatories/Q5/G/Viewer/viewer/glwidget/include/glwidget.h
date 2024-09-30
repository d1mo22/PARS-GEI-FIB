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

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include "scene.h"
#include "camera.h"
#include <QPluginLoader>
//#include <QtOpenGL/qgl.h>
#include <QKeyEvent>
#include <QString>
#include <QFileDialog>
#include <QTimer>
#include <iostream>
#include <vector>
#include <QOpenGLShaderProgram>
#include <string>
using namespace std;

class Plugin;

// see Qt docs, "Creating shared libraries"
#ifdef PLUGINGLWIDGET_LIBRARY
#define PLUGINGLWIDGET_EXPORT Q_DECL_EXPORT
#else
#define PLUGINGLWIDGET_EXPORT Q_DECL_IMPORT
#endif

/*!
    /class GLWidget
    /brief The GLWidget class handles OpenGL rendering through plugins.
*/     

class  GLWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    /*!
    Creates a GLWidget.
    */
    PLUGINGLWIDGET_EXPORT GLWidget(const string& args);

    /*!
    Returns a pointer to the 3D scene.
    */
    PLUGINGLWIDGET_EXPORT Scene* scene();

    /*!
    Returns a pointer to the camera. 
    */
    PLUGINGLWIDGET_EXPORT Camera* camera();

    /*!
    Returns a basic, default shader program 
    */
    PLUGINGLWIDGET_EXPORT QOpenGLShaderProgram* defaultProgram();

    /*!
    Sets the path where plugins will be searched into.
    */
    PLUGINGLWIDGET_EXPORT void setPluginPath(const QString &);

    /*!
      Gets the path where the plugin dynamic libraries are.
    */
    PLUGINGLWIDGET_EXPORT const QString& getPluginPath() const;

public slots:
    /*!
    Opens a file dialog enabling the user to select one or more OBJ files to add to the scene.
    All loaded plugins get their onObjectAdd() method invoked for each loaded object.
    */
    PLUGINGLWIDGET_EXPORT void addObject();

    /*!
    Adds an OBJ file to the scene.
    All loaded plugins get their onObjectAdd() method invoked. 
    */
    PLUGINGLWIDGET_EXPORT void addObjectFromFile(const QString& filename);

    /*!
    Clears the scene (removes all OBJs)
    All loaded plugins get their onSceneClear() method invoked. 
    */
    PLUGINGLWIDGET_EXPORT void clearScene();

    /*!
    Resets the camera so that the whole scene (including world axes) is visible.
    */
    PLUGINGLWIDGET_EXPORT void resetCamera();

    /*!
    Draws three lines representing world space axes.
    */
    PLUGINGLWIDGET_EXPORT void drawAxes();

    /*!
    Draws a point at the given 3D position with the given color.
    */
    PLUGINGLWIDGET_EXPORT void drawPoint(const Vector& pos, float r, float g, float b); 

    /*!
    Returns the bounding box of the scene, enlarged to include also a representation of the world axes.
    */
    PLUGINGLWIDGET_EXPORT Box boundingBoxIncludingAxes() ;

    /*!
    Opens a file dialog enabling the user to select one or more plugins to load.
    After loading each plugin, its onPluginLoad() method is invoked.
    */
    PLUGINGLWIDGET_EXPORT void loadPlugin();

    /*!
    Loads one plugins and calls its onPluginLoad() method.
    */
    PLUGINGLWIDGET_EXPORT int loadPlugins(const QStringList& list);

    /*!
    Loads default plugins.
    */
    PLUGINGLWIDGET_EXPORT void loadDefaultPlugins(QString& plugins);

    /*!
      Unloads all non-default plugins.
    */
    void resetPluginsToDefaults();

    /*!
      Unloads plugin at position i, if within range. 
      otherwise == NOP.
    */
    void unloadPlugin(int i);

    
private:
    void help(void);
    void showPlugins() const;

    virtual void initializeGL() Q_DECL_OVERRIDE;
    virtual void paintGL( void ) Q_DECL_OVERRIDE;
    virtual void resizeGL (int width, int height) Q_DECL_OVERRIDE;

    virtual void keyPressEvent(QKeyEvent *e) Q_DECL_OVERRIDE;
    virtual void mousePressEvent( QMouseEvent *e) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent( QMouseEvent *) Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    virtual void keyReleaseEvent ( QKeyEvent *e) Q_DECL_OVERRIDE;
    virtual void wheelEvent ( QWheelEvent *e) Q_DECL_OVERRIDE;
    
private:
    void executeTest();
    Scene pscene;  
    Camera pcamera;
    QString pluginPath;

    string mainArgs;
    bool grading;
    bool gradingPlugin;
    string pluginToGrade;
    bool defaultsLoaded;
    
    Plugin* drawPlugin;
    vector<QPluginLoader*> plugins;
    QOpenGLShaderProgram unlitProgram; // default (unlit) program
};

#endif


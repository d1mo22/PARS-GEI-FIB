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

#ifndef _BASIC_PLUGIN_H
#define _BASIC_PLUGIN_H

//#include "GL/glew.h"
#include <QtPlugin>
#include <QWidget>
#include "glwidget.h"

//class GLWidget;

/*!
    /class Plugin
    /brief The Plugin class is the base class for all plugins.

    All plugins you will have to implement must derive from this class. 

    All methods have a default implementation (do nothing), so each plugin can override
    only those methods needed to provide the intended functionality. 

    An <em> Effect Plugin </em> might override preFrame() and postFrame() methods
    to modify the OpenGL state before and after the scene is rendered (for example, to load shaders
    or to enable alphablending) and to draw additional content (for example, the frame rate).

    A <em> Draw Plugin </em> might override the drawScene() method, which is in charge of drawing
    all the objects forming the scene by issuing OpenGL rendering commands. 

    An <em> Action Plugin </em> might override user input methods such as keyPressEvent(), mouseMoveEvent()
    to allow for some interaction: camera control, object selection...

    A <em> Render Plugin </em> should override paintGL(). The main purpose is to implement techniques
    requiring multiple rendering passes, for example, shadow mapping. 

*/
class Plugin
{	
public:
    /*!
    Constructs a basic plugin.
    */
    Plugin() : pdrawPlugin(0) {} 

    /*!
    Destroys the plugin.
    */ 
    virtual ~Plugin() {}

    // general methods
    /*!
    This method is called right after the plugin has been loaded by the application. 
    A valid OpenGL context allways exists when this method is invoked. 
    This method usually has code for initializing the plugin: compile shaders, load textures, setup timers...
    The scene might contain some objects but it could also be empty.
    */
    virtual void onPluginLoad() {}

    /*!
    This method is called everytime a new object is added to the scene. 
    This allows your plugin to execute some code everytime the scene has changed.
    */
    virtual void onObjectAdd() {}

    /*!
    This method is called everytime the scene is cleared (all objects are removed).
    This allows your plugin to execute some code everytime the scene has been cleared.
    */
    virtual void onSceneClear() {}

    // methods for "effect" plugins
    /*!
    This method is called in GLWidget::paintGL() before drawing the scene. 
    This allows your plugin to execute some code to be executed right before the scene is rendered.
    A typical use would be to bind a shader affecting the whole scene. 
    Notice that glClear() is likely to be called after all preFrame() methods have been executed,
    so you should not draw anything here. For drawing additional primitives override the 
    postFrame() method instead. 
    */
    virtual void preFrame() {}

    /*!
    This method is called in GLWidget::paintGL() after drawing the scene. 
    This allows your plugin to execute some code to be executed right after the scene is rendered.
    A typical use would be to unbind a shader, or drawing additional primitives (for example,
    the frame rate or a wireframe box around the selected object).
    */
    virtual void postFrame() {}
	
    // methods for "action" plugins	
    /*!
    See the QOpenGLWidget reference.
    */
    virtual void keyPressEvent ( QKeyEvent *  ){}
    /*!
    See the QOpenGLWidget reference.
    */
    virtual void keyReleaseEvent ( QKeyEvent *  ) {}
    /*!
    See the QOpenGLWidget reference.
    */
    virtual void mouseMoveEvent ( QMouseEvent *  ) {}
    /*!
    See the QOpenGLWidget reference.
    */
    virtual void mousePressEvent ( QMouseEvent *  ) {}
    /*!
    See the QOpenGLWidget reference.
    */
    virtual void mouseReleaseEvent ( QMouseEvent *  ) {}
    /*!
    See the QOpenGLWidget reference.
    */
    virtual void wheelEvent ( QWheelEvent *  ) {}

    // methods for "render" plugins
    /*!
    This method is invoked by GLWidget::paintGL(). 
    It is responsible of painting everything whenever the widget needs to be painted. 
    A minimal implementation should call glClear and then invoke the drawScene() method
    of the current <em> Draw Plugin </em>:
    @code
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        if (drawPlugin()) drawPlugin()->drawScene();
        return true;
    @endcode
    If you override paintGL(), you must always return true so that the application
    knows it has been repainted successfully. 
    */
    virtual bool paintGL() {return false;}

    // methods for "draw" plugins
    /*!
    This method is intended to be involked by any plugin willing to draw the scene. 
    For example, a plugin overriding paintGL().
    If you override drawScene(), you must always return true so that the application
    knows the scene has been drawn successfully. 
    The GLWidget class keeps track of the plugin overriding this method.
    Using legacy code, a minimal implementation could be:
    @code
        bool MyPluginExample::drawScene()
        {
            for (unsigned int i=0; i<scene()->objects().size(); ++i) 
            {
                const Object& obj = scene()->objects()[i];
                for (unsigned int c=0; c<obj.faces().size(); c++)
                {
                    const Face& face = obj.faces()[c];
                    glBegin(GL_POLYGON);
                    glNormal3f(face.normal().x(), face.normal().y(), face.normal().z());
                    for(int v=0; v<face.numVertices(); v++)
                    { 
                        const Point& p = obj.vertices()[face.vertexIndex(v)].coord();
                        glVertex3f(p.x(), p.y(), p.z());
                    }
                    glEnd();
                }
            }
            return true; 
        }
    @endcode
    */ 
    virtual bool drawScene() {return false;}

    /*!
    Draws the i-th object in the scene
    */
    virtual bool drawObject(int ) {return false;}


    // access to application components
    /*!
    Returns a pointer to the Scene.
    */
    Scene* scene() {return pglwidget->scene();}

    /*!
    Returns a pointer to the Camera.
    */
    Camera* camera() {return pglwidget->camera();}

    /*!
    Returns a pointer to a plugin implementing drawScene().
    If no such a plugin has been loaded, returns null.
    */
    Plugin* drawPlugin() {return pdrawPlugin;}

    /*!
    Returns a pointer to the GLWidget.
    */
    GLWidget* glwidget() {return pglwidget;}

    // internal methods
    void setWidget(GLWidget* glwidget) {pglwidget = glwidget; }
    void setDrawPlugin(Plugin* drawPlugin) {pdrawPlugin = drawPlugin;}
    void setArgs(const string& str) {pargs = str;} 
    string args() const {return pargs;}

 private:
    GLWidget* pglwidget;
    Plugin* pdrawPlugin;
    string pargs;
 };

Q_DECLARE_INTERFACE(Plugin, "edu.upc.fib.graug.Plugin/1.0"); 

#endif
 
 

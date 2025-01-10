#ifndef _REFLECTION_H
#define _REFLECTION_H

#include "plugin.h" 

class Reflection: public QObject, public Plugin
{
     Q_OBJECT
     Q_PLUGIN_METADATA(IID "Plugin")   
     Q_INTERFACES(Plugin)

 public:
    void onPluginLoad();
    bool paintGL();
 
 private:
   void createMirror(GLWidget & widget);
	void drawMirror(GLWidget & widget);
	void onObjectAdd();
	QMatrix4x4 reflectionMatrix(float a, float b, float c, float d);

    QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs;  
    GLuint textureId, mirrorId;
 };

#endif

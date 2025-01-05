#ifndef _SHADOWVOLUME_H
#define _SHADOWVOLUME_H

#include "plugin.h"

class ShadowVolume: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

   public:
      void onPluginLoad();
      void onSceneClear();
      void onObjectAdd();
      bool paintGL();
	 
   private:
      void loadProgram();
      void sendTriangle(QVector3D, QVector3D, QVector3D);
      void sendFloor();
      void sendShadowVolume(QVector3D, QVector3D, QVector3D, QVector3D);
      void keyPressEvent(QKeyEvent *);
      
      QOpenGLShaderProgram* program;
      QOpenGLShader *fs, *vs; 
   
      GLuint VAOTriangle;
      GLuint VBOTriangleCoords;
      GLuint VBOTriangleColors;
      GLuint VAOFloor;
      GLuint VBOFloorCoords;
      GLuint VBOFloorColors;
      GLuint VAOShadowVolume;
      GLuint VBOShadowCoords;
      
      QVector3D a,b,c;
      QVector3D light;
      
      bool showVolume;
};

#endif

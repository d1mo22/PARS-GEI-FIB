#ifndef _ISAFLOOR_H
#define _ISAFLOOR_H

#include "plugin.h" 

class Isafloor: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

	 void onObjectAdd();
  private:
	// add private methods and attributes here
	float lambda;
	QOpenGLShaderProgram* program;
    QOpenGLShader *fs, *vs; 
};

#endif

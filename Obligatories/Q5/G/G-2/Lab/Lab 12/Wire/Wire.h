#ifndef _WIRE_H
#define _WIRE_H

#include "plugin.h" 

class Wire: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 bool paintGL();
  private:
	// add private methods and attributes here
	QOpenGLShaderProgram* program;
    QOpenGLShader *fs, *vs; 
};

#endif

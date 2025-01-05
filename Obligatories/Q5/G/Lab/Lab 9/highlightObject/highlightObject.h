#ifndef _HIGHLIGHTOBJECT_H
#define _HIGHLIGHTOBJECT_H

#include "plugin.h" 

class HighlightObject: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

	 void onObjectAdd();
	 bool drawScene();
	 bool drawObject(int);

	 bool paintGL();

	 void keyPressEvent(QKeyEvent *);
	 void mouseMoveEvent(QMouseEvent *);
  private:
	// add private methods and attributes here
	void linkShaders();
	void createBox(GLWidget& g);
	void drawBox(GLWidget& g, const Box& box);
	QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
	QOpenGLShader* fs;
	GLuint boxVAO;
};


#endif

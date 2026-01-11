#ifndef _MODELINFO_1_H
#define _MODELINFO_1_H

#include "plugin.h" 

class Modelinfo_1: public QObject, public Plugin
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
	bool printed = false;
	float triangles;
	int objects, vertex, polygons, numTriangles;
};

#endif

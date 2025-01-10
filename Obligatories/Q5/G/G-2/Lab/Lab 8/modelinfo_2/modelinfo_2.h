#ifndef _MODELINFO_2_H
#define _MODELINFO_2_H

#include "plugin.h"
#include <QPainter> 

class Modelinfo_2: public QObject, public Plugin
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
	QPainter painter;
};

#endif

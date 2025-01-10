#include "modelinfo_1.h"
#include "glwidget.h"

void Modelinfo_1::onPluginLoad()
{
	if (!printed) {
		objects = scene()->objects().size();
		vertex = scene()->objects()[0].vertices().size();
		polygons = scene()->objects()[0].faces().size();
		numTriangles = 0;
		for (Face pol : scene()->objects()[0].faces()) {
			if (pol.numVertices() == 3) ++numTriangles;
		}
		triangles = numTriangles / polygons;
	}
}

void Modelinfo_1::preFrame()
{
	
}

void Modelinfo_1::postFrame()
{
	if (!printed) {
		cout << "Total number of objects loades: " << objects << "\n";
		cout << "Total number of ploygons: " << polygons << "\n";
		cout << "Total number of vertex: " << vertex << "\n";
		cout << "Percentage of polygons that are triangles: " << triangles << "% \n";
		printed = true;
	}
}

void Modelinfo_1::onObjectAdd()
{
	
}

bool Modelinfo_1::drawScene()
{
	return false; // return true only if implemented
}

bool Modelinfo_1::drawObject(int)
{
	return false; // return true only if implemented
}

bool Modelinfo_1::paintGL()
{
	return false; // return true only if implemented
}

void Modelinfo_1::keyPressEvent(QKeyEvent *)
{
	
}

void Modelinfo_1::mouseMoveEvent(QMouseEvent *)
{
	
}


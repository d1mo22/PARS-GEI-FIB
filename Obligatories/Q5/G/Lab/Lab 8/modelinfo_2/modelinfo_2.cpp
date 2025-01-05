#include "modelinfo_2.h"
#include "glwidget.h"

void Modelinfo_2::onPluginLoad()
{
	objects = scene()->objects().size();
	vertex = scene()->objects()[0].vertices().size();
	polygons = scene()->objects()[0].faces().size();
	numTriangles = 0;
	for (Face pol : scene()->objects()[0].faces()) {
		if (pol.numVertices() == 3) ++numTriangles;
	}
	triangles = numTriangles / polygons;
}

void Modelinfo_2::preFrame()
{
	
}

void Modelinfo_2::postFrame()
{
	QFont font;
	font.setPixelSize(16);
	painter.begin(glwidget());
	painter.setFont(font);
	int x = 5;
	int y = 20;
	painter.drawText(x, y, "Total number of objects loaded: " + QString::number(objects));
	painter.drawText(x, y+25, "Total number of polygons: " + QString::number(polygons));
	painter.drawText(x, y+50, "Total number of vertex: " + QString::number(vertex));
	painter.drawText(x, y+75, "Percentage of polygons that are triangles: " + QString::number(triangles) + "%");
	painter.end();
}

void Modelinfo_2::onObjectAdd()
{
	
}

bool Modelinfo_2::drawScene()
{
	return false; // return true only if implemented
}

bool Modelinfo_2::drawObject(int)
{
	return false; // return true only if implemented
}

bool Modelinfo_2::paintGL()
{
	return false; // return true only if implemented
}

void Modelinfo_2::keyPressEvent(QKeyEvent *)
{
	
}

void Modelinfo_2::mouseMoveEvent(QMouseEvent *)
{
	
}


#include "showDegree.h"
#include "glwidget.h"

float ShowDegree::computeAverage(const Object& obj) {
	int size = obj.vertices().size();
	int times = 0;
	for (const Face& face: obj.faces()) {
		times += face.numVertices();
	}
	return times / float(size);
}


void ShowDegree::showDegree() {
	QFont font;
	int size = 20;
	font.setPixelSize(size);
	painter.begin(glwidget());
	painter.setFont(font);
	painter.drawText(0, 1 * size, QString::number(grauMitg));
	painter.end();

}

void ShowDegree::onPluginLoad()
{
	grauMitg = computeAverage(scene()->objects()[0]);

}

void ShowDegree::preFrame()
{

}

void ShowDegree::postFrame()
{
	showDegree();
}

void ShowDegree::onObjectAdd()
{
	grauMitg = computeAverage(scene()->objects()[0]);
}

bool ShowDegree::drawScene()
{
	return false; // return true only if implemented
}

bool ShowDegree::drawObject(int)
{
	return false; // return true only if implemented
}

bool ShowDegree::paintGL()
{
	return false; // return true only if implemented
}

void ShowDegree::keyPressEvent(QKeyEvent *)
{
	
}

void ShowDegree::mouseMoveEvent(QMouseEvent *)
{
	
}


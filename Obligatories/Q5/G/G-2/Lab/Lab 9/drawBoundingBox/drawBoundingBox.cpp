#include "drawBoundingBox.h"
#include "glwidget.h"

void DrawBoundingBox::linkShaders() {
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("drawBoundingBox.vert");
	cout << "VS log: " << vs->log().toStdString() << "\n";

	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("drawBoundingBox.frag");
	cout << "FS log: " << fs->log().toStdString() << "\n";

	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
	cout << "Link log: " << program->log().toStdString() << "\n";
}

void DrawBoundingBox::createBox(GLWidget& g) {
	g.glGenVertexArrays(1, &boxVAO);
	g.glBindVertexArray(boxVAO);
	float coordinates[] = {
		1, 1, 0,	 0, 1, 0,
		1, 0, 0,	 0, 0, 0,
		0, 0, 1,	 0, 1, 0,
		0, 1, 1,	 1, 1, 0,
		1, 1, 1,	 1, 0, 0,
		1, 0, 1,	 0, 0, 1,
		1, 1, 1,	 0, 1, 1
	};
	GLuint VBO_coords;
	g.glGenBuffers(1, &VBO_coords);
	g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates), coordinates, GL_STATIC_DRAW);
	g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	g.glEnableVertexAttribArray(0);
	g.glBindVertexArray(0); //Unbind
}	

void DrawBoundingBox::drawBox(GLWidget& g, const Box& box) {
	const Point& translate = box.min();
	const Point& scale = box.max() - box.min();
	program->bind();
	QMatrix4x4 MVP = g.camera()->projectionMatrix() * g.camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", MVP);
	program->setUniformValue("translate", translate);
	program->setUniformValue("scale", scale);
	g.glBindVertexArray(boxVAO);
	g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);
	g.glBindVertexArray(0); //Unbind
}

void DrawBoundingBox::onPluginLoad()
{
	GLWidget &g = *glwidget();
	g.makeCurrent();
	createBox(g);
	linkShaders();
	for (Object& object : g.scene()->objects())
		object.computeBoundingBox();

}

void DrawBoundingBox::preFrame()
{



}

void DrawBoundingBox::postFrame()
{
	GLWidget& g = *glwidget();
	g.makeCurrent();
	GLint ploygonMode;
	g.glGetIntegerv(GL_POLYGON_MODE, &ploygonMode);
	g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (Object& object : g.scene()->objects())
		drawBox(g, object.boundingBox());
	g.glPolygonMode(GL_FRONT_AND_BACK, ploygonMode);
}

void DrawBoundingBox::onObjectAdd()
{
	GLWidget& g = *glwidget();
	g.makeCurrent();
	for (auto object : g.scene()->objects())
		object.computeBoundingBox();
}

bool DrawBoundingBox::drawScene()
{
	return false; // return true only if implemented
}

bool DrawBoundingBox::drawObject(int)
{
	return false; // return true only if implemented
}

bool DrawBoundingBox::paintGL()
{
	return false; // return true only if implemented
}

void DrawBoundingBox::keyPressEvent(QKeyEvent *)
{
	
}

void DrawBoundingBox::mouseMoveEvent(QMouseEvent *)
{
	
}


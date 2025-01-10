#include "highlightObject.h"
#include "glwidget.h"

void HighlightObject::linkShaders() {
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("highlightObject.vert");
	cout << "VS log: " << vs->log().toStdString() << "\n";

	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("highlightObject.frag");
	cout << "FS log: " << fs->log().toStdString() << "\n";

	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
	cout << "Link log: " << program->log().toStdString() << "\n";
}

void HighlightObject::createBox(GLWidget& g) {
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

void HighlightObject::drawBox(GLWidget& g, const Box& box) {
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

void HighlightObject::onPluginLoad()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();
    createBox(g);
    linkShaders();
    for (Object& object : g.scene()->objects())
        object.computeBoundingBox();

}

void HighlightObject::preFrame()
{
	
}

void HighlightObject::postFrame()
{
    GLWidget& g = *glwidget();
    g.makeCurrent();
    GLint polygonMode;
    g.glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
    g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	scene()->setSelectedObject(1);
    int selected = scene()->selectedObject();
	if (selected != -1) {
		drawBox(g, g.scene()->objects()[selected].boundingBox());
	}
        
    g.glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
}

void HighlightObject::onObjectAdd()
{
	GLWidget& g = *glwidget();
	g.makeCurrent();
	for (auto object : g.scene()->objects())
		object.computeBoundingBox();
}

bool HighlightObject::drawScene()
{
	return false; // return true only if implemented
}

bool HighlightObject::drawObject(int)
{
	return false; // return true only if implemented
}

bool HighlightObject::paintGL()
{
	return false; // return true only if implemented
}

void HighlightObject::keyPressEvent(QKeyEvent *)
{
	
}

void HighlightObject::mouseMoveEvent(QMouseEvent *)
{
	
}


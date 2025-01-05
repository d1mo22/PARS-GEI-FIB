#include "animateVertices.h"
#include "glwidget.h"

void AnimateVertices::onPluginLoad()
{
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("animate-vertices1.vert");
	cout << "VS log: " << vs->log().toStdString() << "\n";

	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile("animate-vertices1.frag");
	cout << "FS log: " << fs->log().toStdString() << '\n';

	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
	cout << "Link log: " << program->log().toStdString() << "\n";
	timer.start();
}

void AnimateVertices::preFrame()
{
	program->bind();
	float time = timer.elapsed() / 1000.0f;
	program->setUniformValue("time", time);
	QMatrix4x4 modelView = camera()->viewMatrix();
    QMatrix4x4 MVP = camera()->projectionMatrix() * modelView;
	QMatrix3x3 normalMatrix = modelView.normalMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
	program->setUniformValue("normalMatrix", normalMatrix); 
}

void AnimateVertices::postFrame()
{
	program->release();
}

void AnimateVertices::onObjectAdd()
{
	
}

bool AnimateVertices::drawScene()
{
	return false; // return true only if implemented
}

bool AnimateVertices::drawObject(int)
{
	return false; // return true only if implemented
}

bool AnimateVertices::paintGL()
{
	return false; // return true only if implemented
}

void AnimateVertices::keyPressEvent(QKeyEvent *)
{
	
}

void AnimateVertices::mouseMoveEvent(QMouseEvent *)
{
	
}


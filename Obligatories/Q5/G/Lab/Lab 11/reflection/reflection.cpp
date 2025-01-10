// GLarena, a plugin based platform to teach OpenGL programming
// © Copyright 2012-2018, ViRVIG Research Group, UPC, https://www.virvig.eu
// 
// This file is part of GLarena
//
// GLarena is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "reflection.h"

const int IMAGE_WIDTH = 512;
const int IMAGE_HEIGHT = IMAGE_WIDTH;

void Reflection::createMirror(GLWidget & widget) {
	GLuint VBO;
	const Point & min = widget.scene()->boundingBox().min();
	const Point & max = widget.scene()->boundingBox().max();
	float coords[] = {
		min.x(), min.y(), min.z(), 
		max.x(), min.y(), min.z(),
		min.x(), min.y(), max.z(),
		max.x(), min.y(), max.z()
	};
	widget.glGenVertexArrays(1, &mirrorId);
	widget.glBindVertexArray(mirrorId);
	widget.glGenBuffers(1, &VBO);
	widget.glBindBuffer(GL_ARRAY_BUFFER, VBO);
	widget.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
	widget.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	widget.glEnableVertexAttribArray(0);
	widget.glBindVertexArray(0);
}

QMatrix4x4 Reflection::reflectionMatrix(float a, float b, float c, float d) {
	return QMatrix4x4(
	1 - 2 * a * a,   - 2 * a * b,   - 2 * a * c, - 2 * a * d,
 	  - 2 * a * b, 1 - 2 * b * b,   - 2 * b * c, - 2 * b * d,
	   -2 * a * c,   - 2 * b * c, 1 - 2 * c * c, - 2 * c * d,
	            0,             0,             0,           1
	);
}

void Reflection::onPluginLoad()
{
	GLWidget & g = *glwidget();
	g.makeCurrent();

	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile(g.getPluginPath()+"/../reflection/reflection.vert");
	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceFile(g.getPluginPath()+"/../reflection/reflection.frag");
	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();

	g.glActiveTexture(GL_TEXTURE0);
	g.glGenTextures( 1, &textureId);
	g.glBindTexture(GL_TEXTURE_2D, textureId);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_WIDTH, IMAGE_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
	g.glBindTexture(GL_TEXTURE_2D, 0);
	g.resize(IMAGE_WIDTH,IMAGE_HEIGHT);
	
	createMirror(g);
}

void Reflection::onObjectAdd()
{
	GLWidget & widget = *glwidget();
	widget.makeCurrent();
	createMirror(widget);
}

void Reflection::drawMirror(GLWidget & widget)
{
	widget.glBindVertexArray(mirrorId);
	widget.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	widget.glBindVertexArray(0);
}

bool Reflection::paintGL()
{
	GLWidget & g = *glwidget();
	g.makeCurrent();
	
	program->bind();

	//Preparamos para dibujar a escena reflejada en el espejo
	program->setUniformValue("modelViewProjectionMatrix",
		g.camera()->projectionMatrix() * g.camera()->viewMatrix());
	program->setUniformValue("mirror", false);
	
	g.glClearColor(1, 1, 1, 0);
	g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	program->setUniformValue("reflectionMatrix", reflectionMatrix(0, -1, 0, g.scene()->boundingBox().min().y()));
	if (drawPlugin()) drawPlugin()->drawScene();
	
	//Se copia lo que hemos dibujado (el reflejo) en la textura textureId
	g.glActiveTexture(GL_TEXTURE0); 
	g.glBindTexture(GL_TEXTURE_2D, textureId); // Enlaza el identificador textureId a la unidad de textura 0 como una textura 2D.
	g.glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, IMAGE_WIDTH, IMAGE_HEIGHT); // Copia el contenido actual del framebuffer (la escena reflejada) y lo guarda en una textura asociada a textureId.
	g.glGenerateMipmap(GL_TEXTURE_2D);
	g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // Limpiamos el frameBuffer y el depthBuffer
	
	//Dibujamos la escena normal
	program->setUniformValue("reflectionMatrix", QMatrix4x4());
	if (drawPlugin()) drawPlugin()->drawScene();
	
	program->setUniformValue("colorMap", 0); // Nombre del uniform, ID de la textura
	program->setUniformValue("size", QVector2D(float(IMAGE_WIDTH), float(IMAGE_HEIGHT)));
	program->setUniformValue("mirror", true);

	//Dibujamos el espejo y lo que se vera reflejado
	drawMirror(g);
	
	g.glBindTexture(GL_TEXTURE_2D, 0);
	g.defaultProgram()->bind();
	return true;
}

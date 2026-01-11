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

#include "objectSelect.h"
#include <QCoreApplication>


void ObjectSelect::linkShadersBox() {
	vsBox = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vsBox->compileSourceFile("drawBox.vert");
	cout << "VS log (box): " << vsBox->log().toStdString() << "\n";

	fsBox = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fsBox->compileSourceFile("drawBox.frag");
	cout << "FS log (box): " << fsBox->log().toStdString() << "\n";

	programBox = new QOpenGLShaderProgram(this);
	programBox->addShader(vsBox);
	programBox->addShader(fsBox);
	programBox->link();
	cout << "Link log (box): " << programBox->log().toStdString() << "\n";
}

void ObjectSelect::createBox(GLWidget& g) {
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
	g.glGenVertexArrays(1, &boxVAO);
	g.glBindVertexArray(boxVAO);
	g.glGenBuffers(1, &VBO_coords);
	g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates), coordinates, GL_STATIC_DRAW);
	g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	g.glEnableVertexAttribArray(0);
	g.glBindVertexArray(0); //Unbind
}	

void ObjectSelect::drawBox(GLWidget& g, const Box& box) {
	QMatrix4x4 MVP = g.camera()->projectionMatrix() * g.camera()->viewMatrix();
	const Point& translate = box.min();
	const Point& scale = box.max() - box.min();
    GLint polygonMode;
	programBox->bind();
	programBox->setUniformValue("modelViewProjectionMatrix", MVP);
	programBox->setUniformValue("translate", translate);
	programBox->setUniformValue("scale", scale);
    programBox->setUniformValue("color", QVector4D(0.0f, 0.0f, 0.0f, 1.0f));
    g.glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
	g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	g.glBindVertexArray(boxVAO);
	g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);
	g.glBindVertexArray(0);
	g.glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
	g.defaultProgram()->bind();
}

void ObjectSelect::encodeID(const unsigned int i, GLubyte * color) {
	// complete this method to encode the object index (i) as a color
    GLubyte R = i + 1; // complete
    GLubyte G = 0; // complete
    GLubyte B = 0; // complete
    color[0] = R;
    color[1] = G;
    color[2] = B;
    color[3] = 255;
}

void ObjectSelect::decodeID(const GLubyte *color, unsigned int &i) {
	// complete this method to decode the object index from the color 
    unsigned int R = (unsigned int) color[0];
    unsigned int G = (unsigned int) color[1];
    unsigned int B = (unsigned int) color[2];
	// compute i from R, G, B
    i = R - 1; 
}

void ObjectSelect::onPluginLoad() {
    std::cout << "[ObjectSelect plugin] Ctrl + Right Click - Select object" << std::endl;

    GLWidget &g = *glwidget();
    g.makeCurrent();
    linkShadersBox();
    // Carregar shader, compile & link
    vsSelect = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsSelect->compileSourceFile(g.getPluginPath() + "/../objectSelect/objectSelect.vert");

    fsSelect = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsSelect->compileSourceFile(g.getPluginPath() + "/../objectSelect/objectSelect.frag");

    programSelect = new QOpenGLShaderProgram(this);
    programSelect->addShader(vsSelect);
    programSelect->addShader(fsSelect);
    programSelect->link();
    if (!programSelect->isLinked())
        std::cout << "Shader link error" << std::endl;
    createBox(g);
}

void ObjectSelect::selectDraw(GLWidget & g) {
    // (b)
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // (c)
    programSelect->bind();

    // (d)
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    programSelect->setUniformValue("modelViewProjectionMatrix", MVP);

    // (e)
    for (unsigned int i=0; i<scene()->objects().size(); ++i){
        GLubyte color[4];
        encodeID(i,color);
        programSelect->setUniformValue("color", QVector4D(color[0]/255.0, color[1]/255., color[2]/255., 1.0));
        drawPlugin()->drawObject(i);
    }
}

void ObjectSelect::mouseReleaseEvent(QMouseEvent* e) {
    // (a)
    if (!(e->button() & Qt::RightButton)) return;
    if (e->modifiers() & (Qt::ShiftModifier)) return;
    if (!(e->modifiers() & Qt::ControlModifier)) return;

    GLWidget &g = *glwidget();
    g.makeCurrent();

    // (b) through (e)
    selectDraw(g);

    // (f)
    int x = e->x();
    int y = g.height() - e->y();
    GLubyte read[4];
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, read);

    // (g)
    if(read[3] == 255){
        // Not the background, thus an object has been selected
        unsigned int tmp;
        decodeID(read, tmp);
        scene()->setSelectedObject((int) tmp);
        std::cout << tmp << std::endl;
    } else {
        scene()->setSelectedObject(-1);
        std::cout << -1 << std::endl;
    }

    // (h)
    g.update();
}

void ObjectSelect::postFrame() {
    GLWidget& g = *glwidget();
    g.makeCurrent();
    int id = g.scene()->selectedObject();
    if (id >= 0) drawBox(g, g.scene()->objects()[id].boundingBox());
}

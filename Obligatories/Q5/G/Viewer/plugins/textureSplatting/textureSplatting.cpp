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

#include "textureSplatting.h"
#include <QFileDialog>
 
void TextureSplatting::onPluginLoad()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();
	// VS
    QString vs_src = \
      "#version 330 core\n"
      "uniform float radius = 1.0;"
      "uniform mat4 modelViewProjectionMatrix;"
      "uniform mat3 normalMatrix;"
      "layout (location = 0) in vec3 vertex;"
      "layout (location = 1) in vec3 normal;"
      "out vec2 vtexCoord;"
      "out vec3 vertexNormal;"
      "void main() {"
      "  vtexCoord = (4.0/radius)*(vertex.xy+vertex.zx);"
      "  vertexNormal = normalMatrix * normal;"
      "  gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.);"
      "}";
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceCode(vs_src);
    cout << "VS log:" << vs->log().toStdString() << endl;


	// FS
    QString fs_src =
      "#version 330 core\n"
      "uniform sampler2D sampler0;"
      "uniform sampler2D sampler1;"
      "uniform sampler2D sampler2;"
      "in vec2 vtexCoord;"
      "in vec3 vertexNormal;"
      "out vec4 fragColor;"
      "void main() {"
      "float p = texture(sampler0, vtexCoord).r;"
      "vec4 color1 = texture(sampler1, vtexCoord);"
      "vec4 color2 = texture(sampler2, vtexCoord);"
      "fragColor = mix(color1, color2, p);  }";
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceCode(fs_src);
	cout << "FS log:" << fs->log().toStdString() << endl;


	// Program  
  	program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
	program->addShader(fs);
	program->link();
	cout << "Link log:" << program->log().toStdString() << endl;


	// Load Texture 1
	QString filename = QFileDialog::getOpenFileName(0, "Open Image", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	
	QImage img0(filename);	
	QImage im0 = img0.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
    g.makeCurrent();

	g.glActiveTexture(GL_TEXTURE0);
	g.glGenTextures( 1, &textureId0);
	g.glBindTexture(GL_TEXTURE_2D, textureId0);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);

	// Load Texture 2
	QString filename2 = QFileDialog::getOpenFileName(0, "Open Image 2", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	
	QImage img1(filename2);	
	QImage im1 = img1.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
    g.makeCurrent();

	g.glActiveTexture(GL_TEXTURE1);
	g.glGenTextures( 1, &textureId1);
	g.glBindTexture(GL_TEXTURE_2D, textureId1);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im1.width(), im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);

    // Load Texture 2
	QString filename3 = QFileDialog::getOpenFileName(0, "Open Image 3", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	
	QImage img2(filename3);	
	QImage im2 = img2.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
    g.makeCurrent();

	g.glActiveTexture(GL_TEXTURE1);
	g.glGenTextures( 1, &textureId2);
	g.glBindTexture(GL_TEXTURE_2D, textureId2);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im2.width(), im2.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im2.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureSplatting::preFrame() 
{
    GLWidget &g = *glwidget();
    g.makeCurrent();

    // bind shader and define uniforms
    program->bind();
    program->setUniformValue("sampler0", 0);  // texture unit del primer sampler 
    program->setUniformValue("sampler1", 1);  // texture unit del segon  sampler 
    program->setUniformValue("sampler2", 2);   // texture unit del tercer sampler
    program->setUniformValue("radius", float(scene()->boundingBox().radius()));  // radi d'una esfera que engloba l'escena
    program->setUniformValue("normalMatrix", g.camera()->viewMatrix().normalMatrix());
    program->setUniformValue("modelViewProjectionMatrix", g.camera()->projectionMatrix() * g.camera()->viewMatrix());
    // bind textures
    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, textureId0);
    g.glActiveTexture(GL_TEXTURE1);
    g.glBindTexture(GL_TEXTURE_2D, textureId1);
    g.glActiveTexture(GL_TEXTURE2);
    g.glBindTexture(GL_TEXTURE_2D, textureId2);
}

void TextureSplatting::postFrame() 
{
    GLWidget &g = *glwidget();
    g.makeCurrent();

    // bind default shaders
    g.defaultProgram()->bind();
    // unbind textures
    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    g.glActiveTexture(GL_TEXTURE1);
    g.glBindTexture(GL_TEXTURE_2D, 0);
}


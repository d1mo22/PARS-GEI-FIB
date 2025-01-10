#include "Wire.h"
#include "glwidget.h"

void Wire::onPluginLoad() {
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
      "out vec4 fcolor;"
      "void main() {"
      "  vertexNormal = normalMatrix * normal;"
      "  fcolor = vec4(vertexNormal.z);"
      "  gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.);"
      "}";
    
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceCode(vs_src);
    cout << "VS log:" << vs->log().toStdString() << endl;

	// FS
    QString fs_src =
      "#version 330 core\n"
      "uniform bool outline;"
      "in vec3 vertexNormal;"
      "in vec4 fcolor;"
      "out vec4 fragColor;"
      "void main() {"
      " if(outline) fragColor = vec4(0);"
      " else fragColor = fcolor;  }";
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceCode(fs_src);
	cout << "FS log:" << fs->log().toStdString() << endl;


	// Program  
    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
	program->addShader(fs);
	program->link();
	cout << "Link log:" << program->log().toStdString() << endl;
}

bool Wire::paintGL()
{
    GLWidget& g = *glwidget();
    g.makeCurrent();

    program->bind();
    program->setUniformValue("normalMatrix", g.camera()->viewMatrix().normalMatrix());
    program->setUniformValue("modelViewProjectionMatrix", g.camera()->projectionMatrix() * g.camera()->viewMatrix());

    g.glClearColor(1, 1, 1, 0);
	g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    program->setUniformValue("outline", false);
    g.glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    g.glEnable(GL_POLYGON_OFFSET_FILL);
    g.glPolygonOffset(1,1);
    if (drawPlugin()) drawPlugin()->drawScene();
    g.glDisable(GL_POLYGON_OFFSET_FILL);

    program->setUniformValue("outline", true);
    g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (drawPlugin()) drawPlugin()->drawScene();

    g.glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	return true; // return true only if implemented
}


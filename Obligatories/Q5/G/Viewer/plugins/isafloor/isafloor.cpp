#include "isafloor.h"
#include "glwidget.h"

void Isafloor::onPluginLoad()
{
    float totalArea = 0.0;
    float floorArea = 0.0;
    
    const Object& obj = scene()->objects()[0];
    
    for (const Face& face : obj.faces()) {
        // Obtener vértices del triángulo
        Point p1 = obj.vertices()[face.vertexIndex(0)].coord();
        Point p2 = obj.vertices()[face.vertexIndex(1)].coord();
        Point p3 = obj.vertices()[face.vertexIndex(2)].coord();
        
        // Calcular vectores del triángulo
        Vector v1 = p2 - p1;
        Vector v2 = p3 - p1;
        
        // Área = |v1 × v2| / 2
        float area = Vector::crossProduct(v1, v2).length() / 2.0;
        
        // Normal unitaria
        Vector normal = face.normal();
        normal.normalize();
        
        // Producto escalar con (0,0,1) en world space
        float dot = Vector::dotProduct(normal, Vector(0,0,1));
        
        totalArea += area;
        if (dot > 0.7) floorArea += area;
    }
    
    lambda = (totalArea > 0) ? floorArea/totalArea : 0;
    cout << "TERRA: " << lambda << endl;
}

void Isafloor::preFrame()
{
	GLWidget& g = *glwidget();
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceCode("isafloor.vert");

	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceCode("isafloor.frag");

	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();

	program->bind();
    program->setUniformValue("lambda", lambda);
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    QMatrix3x3 normalMatrix;
	g.glGetFloatv(GL_NORMAL_MATRIX, normalMatrix)
    program->setUniformValue("normalMatrix", normalMatrix);
}

void Isafloor::postFrame()
{
	//cout << "TERRA: " << lambda << endl;
}

void Isafloor::onObjectAdd()
{
	
}



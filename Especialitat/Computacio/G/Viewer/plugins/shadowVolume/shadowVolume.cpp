#include "shadowVolume.h"
#include "glwidget.h"

void ShadowVolume::onPluginLoad()
{
   GLWidget &g = *glwidget();
   g.makeCurrent();
   
   showVolume = false;
   
   loadProgram();
   
   scene()->computeBoundingBox();
   Box box = scene()->boundingBox();
   Point p = box.max();
   float d = 0.2*box.radius();
   
   // oclusor
   a = QVector3D(p.x(), p.y()+d, p.z());
   b = QVector3D(p.x()-3*d, p.y()+d, p.z());
   c = QVector3D(p.x()-3*d, p.y()+d, p.z()-3*d);
   // lightPos
   light = QVector3D(p.x(), p.y()+2*d, p.z());
   
   sendTriangle(a, b, c);
   sendFloor();
   sendShadowVolume(a, b, c, light);
}

void ShadowVolume::onSceneClear()
{
   GLWidget & g = *glwidget();

   g.glDeleteBuffers (1, &VBOTriangleCoords);
   g.glDeleteBuffers (1, &VBOTriangleColors);
   g.glDeleteVertexArrays (1, &VAOTriangle);
   
   g.glDeleteBuffers (1, &VBOFloorCoords);
   g.glDeleteBuffers (1, &VBOFloorColors);
   g.glDeleteVertexArrays (1, &VAOFloor);
   
   g.glDeleteBuffers (1, &VBOShadowCoords);
   g.glDeleteVertexArrays (1, &VAOShadowVolume);
}

void ShadowVolume::onObjectAdd()
{
   GLWidget &g = *glwidget();
   g.makeCurrent();
   scene()->computeBoundingBox();
   Box box = scene()->boundingBox();
   Point p = box.max();
   float d = 0.2*box.radius();
   
   // oclusor
   a = QVector3D(p.x(), p.y()+d, p.z());
   b = QVector3D(p.x()-3*d, p.y()+d, p.z());
   c = QVector3D(p.x()-3*d, p.y()+d, p.z()-3*d);
   // lightPos
   light = QVector3D(p.x(), p.y()+2*d, p.z());
  
   sendTriangle(a, b, c);
   sendFloor();
   sendShadowVolume(a, b, c, light);
}

bool ShadowVolume::paintGL()
{
   GLWidget & g = *glwidget();
   
   program->bind();
   QMatrix4x4 PVM = camera()->projectionMatrix() * camera()->viewMatrix();
   program->setUniformValue("modelViewProjectionMatrix", PVM);
   program->setUniformValue("dark", float(1.0));
   
   g.glClearColor(1,1,1,0);
   g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
   
   if (showVolume) {
      // Step 1. Draw scene
  
      // draw oclusor
      g.glBindVertexArray(VAOTriangle);
      g.glDrawArrays(GL_TRIANGLES, 0, 3);
   
      // draw floor
      g.glBindVertexArray(VAOFloor);
      g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
      
      // draw shadow volume
      g.glBindVertexArray(VAOShadowVolume);
      g.glDrawArrays(GL_TRIANGLES, 0, 24);
      
      // draw objects
      if (drawPlugin()) drawPlugin()->drawScene();
   
   }
   else {
   
      // Step 1. Draw scene to z-buffer
      g.glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
   
      // draw oclusor
      g.glBindVertexArray(VAOTriangle);
      g.glDrawArrays(GL_TRIANGLES, 0, 3);
   
      // draw floor
      g.glBindVertexArray(VAOFloor);
      g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
      
      // draw objects
      if (drawPlugin()) drawPlugin()->drawScene();
      
      // Step 2. Draw shadow volume front faces to stencil
      glEnable(GL_STENCIL_TEST);
      glDepthMask(GL_FALSE);
      glStencilFunc(GL_ALWAYS, 0, 0);
      glEnable(GL_CULL_FACE);
      glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
      glCullFace(GL_BACK);
      g.glBindVertexArray(VAOShadowVolume);
      g.glDrawArrays(GL_TRIANGLES, 0, 24);
   
      // Step 3. Draw shadow volume back faces to stencil
      g.glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
      g.glCullFace(GL_FRONT);
      g.glBindVertexArray(VAOShadowVolume);
      g.glDrawArrays(GL_TRIANGLES, 0, 24);
   
      // Step 4. Draw dark area of the scene
	  // completeu el codi per configurar correctament l'estat d'OpenGL (Depth & Color Masks, Depth function, Config. Stencil, face culling)

      program->setUniformValue("dark", float(0.2));
   
      // draw oclusor
      g.glBindVertexArray(VAOTriangle);
      g.glDrawArrays(GL_TRIANGLES, 0, 3);
   
      // draw floor
      g.glBindVertexArray(VAOFloor);
      g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
   
      // draw objects
      if (drawPlugin()) drawPlugin()->drawScene();

      // Step 5. Draw light area of the scene
	  // completeu el codi per configurar correctament la funció de stencil
		

      program->setUniformValue("dark", float(1.0));
   
      // draw oclusor
      g.glBindVertexArray(VAOTriangle);
      g.glDrawArrays(GL_TRIANGLES, 0, 3);
   
      // draw floor
      g.glBindVertexArray(VAOFloor);
      g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
   
      // draw objects
      if (drawPlugin()) drawPlugin()->drawScene();
   
      // Step 6. Restore initial values
      g.glDepthFunc(GL_LESS);
      g.glDisable(GL_STENCIL_TEST);
   }
   
   g.glBindVertexArray(0);
   
   return true;
}

void ShadowVolume::keyPressEvent (QKeyEvent *e)
{
   GLWidget & g = *glwidget();
   g.makeCurrent();
   
   if (e->key() == Qt::Key_C) {
      QVector4D p = camera()->viewMatrix().inverted() * QVector4D(0,0,0,1);
      light = QVector3D(p.x(),p.y(),p.z());
      sendShadowVolume(a,b,c,light);
   }
   else if (e->key() == Qt::Key_S) {
      showVolume = !showVolume;
   }
   
   g.update();
}

void ShadowVolume::loadProgram()
{
    // Carregar shader, compile & link 
    QString vs_src =
      "#version 330 core\n"
      "layout (location = 0) in vec3 vertex;"
      "layout (location = 1) in vec3 color;"
      "out vec4 frontColor;"
      "uniform mat4 modelViewProjectionMatrix;"
      "uniform float dark = 1.0;"
      "void main() {"
      "    frontColor = vec4(color,1.0) * dark;"
      "    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);}";
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceCode(vs_src);
    cout << "VS log:" << vs->log().toStdString() << endl;

    QString fs_src =
      "#version 330 core\n"
      "in vec4 frontColor;"
      "out vec4 fragColor;"
      "void main() {"
      "    fragColor = frontColor;}";
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceCode(fs_src);
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;
}

void ShadowVolume::sendTriangle(QVector3D a, QVector3D b, QVector3D c)
{
   GLWidget &g = *glwidget();
   float coord[] = {a.x(), a.y(), a.z(),
                    b.x(), b.y(), b.z(),
                    c.x(), c.y(), c.z()};
   float color[] = {1.0, 1.0, 0.0,
                    1.0, 1.0, 0.0,
                    1.0, 1.0, 0.0};
                    
   g.glDeleteBuffers (1, &VBOTriangleCoords);
   g.glDeleteBuffers (1, &VBOTriangleColors);
   g.glDeleteVertexArrays (1, &VAOTriangle);
                    
   g.glGenVertexArrays (1,&VAOTriangle);
   
   g.glGenBuffers(1, &VBOTriangleCoords);
   g.glBindVertexArray (VAOTriangle);
   g.glBindBuffer (GL_ARRAY_BUFFER, VBOTriangleCoords);
   g.glBufferData (GL_ARRAY_BUFFER, sizeof(coord), &coord[0], GL_STATIC_DRAW);
   g.glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);
   g.glEnableVertexAttribArray (0);
   
   g.glGenBuffers(1, &VBOTriangleColors);   
   g.glBindBuffer (GL_ARRAY_BUFFER, VBOTriangleColors);
   g.glBufferData (GL_ARRAY_BUFFER, sizeof(color), &color[0], GL_STATIC_DRAW);
   g.glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, 0);
   g.glEnableVertexAttribArray (1);
   
   g.glBindVertexArray (0);
}

void ShadowVolume::sendFloor()
{
   GLWidget &g = *glwidget();
   Box b = scene()->boundingBox();
   float coord[] = {b.center().x()-b.radius(),  b.min().y(), b.center().z()+b.radius(),
                    b.center().x()+b.radius(),  b.min().y(), b.center().z()+b.radius(),
                    b.center().x()-b.radius(),  b.min().y(), b.center().z()-b.radius(),
                    b.center().x()+b.radius(),  b.min().y(), b.center().z()-b.radius()};
   float color[] = {0.6, 0.6, 0.6,
                    0.6, 0.6, 0.6,
                    0.6, 0.6, 0.6,
                    0.6, 0.6, 0.6};
   
   g.glDeleteBuffers (1, &VBOFloorCoords);
   g.glDeleteBuffers (1, &VBOFloorColors);
   g.glDeleteVertexArrays (1, &VAOFloor);
   
   g.glGenVertexArrays (1,&VAOFloor);
   
   g.glGenBuffers(1, &VBOFloorCoords);
   g.glBindVertexArray (VAOFloor);
   g.glBindBuffer (GL_ARRAY_BUFFER, VBOFloorCoords);
   g.glBufferData (GL_ARRAY_BUFFER, sizeof(coord), &coord[0], GL_STATIC_DRAW);
   g.glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);
   g.glEnableVertexAttribArray (0);
   
   g.glGenBuffers(1, &VBOFloorColors);   
   g.glBindBuffer (GL_ARRAY_BUFFER, VBOFloorColors);
   g.glBufferData (GL_ARRAY_BUFFER, sizeof(color), &color[0], GL_STATIC_DRAW);
   g.glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, 0);
   g.glEnableVertexAttribArray (1);
   
   g.glBindVertexArray (0);
}

void ShadowVolume::sendShadowVolume(QVector3D a, QVector3D b, QVector3D c, QVector3D light)
{
   GLWidget &g = *glwidget();
   
   Box bo = scene()->boundingBox();
   float scale = (a.y()-bo.min().y())/(light.y()-a.y());
      
   QVector3D La = a-light;
   QVector3D Lb = b-light;
   QVector3D Lc = c-light;
   QVector3D Ba = scale*La;
   QVector3D Bb = scale*Lb;
   QVector3D Bc = scale*Lc;
   
   float coord[] = {// oclusor
                    a.x(), a.y(), a.z(),
                    b.x(), b.y(), b.z(),
                    c.x(), c.y(), c.z(),
                    
                    // face 1
                    a.x(), a.y(), a.z(),
                    b.x(), b.y(), b.z(),
                    Bb.x(), Bb.y(), Bb.z(),
                    Bb.x(), Bb.y(), Bb.z(),
                    Ba.x(), Ba.y(), Ba.z(),
                    a.x(), a.y(), a.z(),
                    
                    // face 2
                    b.x(), b.y(), b.z(),
                    c.x(), c.y(), c.z(),
                    Bc.x(), Bc.y(), Bc.z(),
                    Bc.x(), Bc.y(), Bc.z(),
                    Bb.x(), Bb.y(), Bb.z(),
                    b.x(), b.y(), b.z(),
                    
                    // face 3
                    c.x(), c.y(), c.z(),
                    a.x(), a.y(), a.z(),
                    Ba.x(), Ba.y(), Ba.z(),
                    Ba.x(), Ba.y(), Ba.z(),
                    Bc.x(), Bc.y(), Bc.z(),
                    c.x(), c.y(), c.z(),
                    
                    // bottom
                    Ba.x(), Ba.y(), Ba.z(),
                    Bb.x(), Bb.y(), Bb.z(),
                    Bc.x(), Bc.y(), Bc.z(),
                    };
                    
   g.glDeleteBuffers (1, &VBOShadowCoords);
   g.glDeleteVertexArrays (1, &VAOShadowVolume);
   
   g.glGenVertexArrays (1,&VAOShadowVolume);
   g.glGenBuffers(1, &VBOShadowCoords);
   g.glBindVertexArray (VAOShadowVolume);
   g.glBindBuffer (GL_ARRAY_BUFFER, VBOShadowCoords);
   g.glBufferData (GL_ARRAY_BUFFER, sizeof(coord), &coord[0], GL_STATIC_DRAW);
   g.glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);
   g.glEnableVertexAttribArray (0);
   
   g.glBindVertexArray (0);
}

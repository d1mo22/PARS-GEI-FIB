#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL) {
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget () {
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL () {
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffersQuadrat();
}


void MyGLWidget::modelTransformQuadrat(glm::vec3 posicio, glm::vec3 escala) {
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG,posicio);  
  TG = glm::scale(TG,escala);
  glUniformMatrix4fv(TGLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformQuadratCano(glm::vec3 posicio, glm::vec3 escala) {
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, posicio);
  TG = glm::scale(TG, escala);
  glUniformMatrix4fv(TGLoc, 1, GL_FALSE, &TG[0][0]);

}

//36 graus = pi/5
//30 grados = pi/6
void MyGLWidget::modelTransformQuadrat_Roda(glm::vec3 centre, float separacio_entre_rectangles, bool rectangle_negre) {
  glm::mat4 TG(1.0);
  float offset = -0.5;
  for (int i = 0; i < 1; ++i) {
    TG = glm::mat4(1.0); // Restaurar la matriz de transformación a la identidad en cada iteración
    // Aplicar la traslación a la posición relativa al centro
    
    //TG = glm::rotate(TG, (float) (i * M_PI / 6), glm::vec3(0.0,0.0,1.0));
    // Aplicar la escala
    TG = glm::translate(TG, glm::vec3(-0.275, -0.125, 0.0));
    TG = glm::scale(TG, glm::vec3(0.1, 0.05, 0.0));
    // Aplicar transformaciones adicionales si el rectángulo es negro
    if (rectangle_negre && (i % 2 == 0)) {
      // Aplicar color negro
      glUniform3fv(colorLoc, 1, &negre[0]);
    } else {
      // Aplicar color gris
      glUniform3fv(colorLoc, 1, &gris[0]);
    }
    // Enviar la matriz de transformación al shader
    glUniformMatrix4fv(TGLoc, 1, GL_FALSE, &TG[0][0]);
    // Dibujar el rectángulo
    glDrawArrays(GL_TRIANGLES, 0, 6);
    offset += 0.1;
  }
}



void MyGLWidget::paintGL () {
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

  // Pintem un quadrat
  glBindVertexArray(VAOQuadrat);
  glUniform3fv(colorLoc, 1, &verd[0]);
  modelTransformQuadrat(glm::vec3(0.5, 0.0, 0.0), glm::vec3(1.0, 0.25, 0.0));
  glDrawArrays(GL_TRIANGLES, 0, 6);  

  modelTransformQuadrat(glm::vec3(0.375, 0.25, 0.0), glm::vec3(0.5, 0.25, 0.0));
  glDrawArrays(GL_TRIANGLES, 0, 6); 

  glUniform3fv(colorLoc, 1, &gris[0]);
  modelTransformQuadratCano(glm::vec3(0.875, 0.1875, 0.0), glm::vec3(0.75, 0.125, 0.0));
  glDrawArrays(GL_TRIANGLES, 0, 6); 

  modelTransformQuadrat_Roda(glm::vec3(-0.375, -0.125, 0.0), 0.25, true);
  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h) {
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif
}
// 1 grados = pi/180
void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_Left: 
    	break;
    case Qt::Key_Right: 
    	break;
    case Qt::Key_A: 
    	break;
    case Qt::Key_D:
    	break;		
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::creaBuffersQuadrat () {
  glm::vec3 Vertices[6];  // vèrtexs amb X, Y i Z
  
  // minX = -1.0
  // maxX = 0.0
  // minY = -1.0
  // maxY = 0.0
  
  Vertices[0] = glm::vec3(-1.0, 0.0, 0);
  Vertices[1] = glm::vec3( 0.0, -1.0, 0);
  Vertices[2] = glm::vec3( 0.0, 0.0, 0);
  Vertices[3] = glm::vec3( 0.0, -1.0, 0);
  Vertices[4] = glm::vec3( -1.0, 0.0, 0);
  Vertices[5] = glm::vec3( -1.0, -1.0, 0);
  
  glm::vec3 ColorVerd[6];
  for (int i = 0; i < 6; ++i) {
    ColorVerd[i] = verd;
  }

  glm::vec3 ColorGris[6];
  for (int i = 0; i < 6; ++i) {
    ColorGris[i] = gris;
  }
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar el quadrat
  glGenVertexArrays(1, &VAOQuadrat);
  glBindVertexArray(VAOQuadrat);

  // Creació del buffer amb les posicions dels vèrtexs
  GLuint VBOUnder, VBOColor;
  glGenBuffers(1, &VBOUnder);
  glGenBuffers(1, &VBOColor);
  
  glBindBuffer(GL_ARRAY_BUFFER, VBOUnder);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Desactivem el VAO
  glBindVertexArray(0);
}


void MyGLWidget::carregaShaders() {
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  
  // Obtenim els identificadors dels uniforms
  TGLoc = glGetUniformLocation(program->programId(), "TG"); 
  colorLoc = glGetUniformLocation (program->programId(), "color");
}

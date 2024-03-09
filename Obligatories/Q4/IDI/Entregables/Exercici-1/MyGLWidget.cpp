#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffersQuadrat();
}


void MyGLWidget::modelTransformQuadrat(glm::vec3 posicio, glm::vec3 escala)
{
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG,posicio);  
  TG = glm::scale(TG,escala);
  glUniformMatrix4fv(TGLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformRoda(glm::vec3 posicio, float angle) {
  glm::mat4 TG(1.0f);
  //TG = glm::rotate(TG, (float) M_PI/8, glm::vec3(-0.43, -0.1, 1));
  glUniformMatrix4fv(TGLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::paintGL()
{
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

  // Pintem un quadrat
  glBindVertexArray(VAO[0]);
  modelTransformQuadrat(glm::vec3(0.0), glm::vec3(1.0));
  glDrawArrays(GL_TRIANGLES, 0, 12);  

  glBindVertexArray(VAO[1]);
  glDrawArrays(GL_TRIANGLES, 0, 6);  

  glBindVertexArray(VAO[2]);
  modelTransformRoda(glm::vec3(0.0), 0.0);
  glDrawArrays(GL_TRIANGLES, 0, 6); 
  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
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

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
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

void MyGLWidget::creaBuffersQuadrat ()
{
  //Color verd = vec4(0.20, 0.60, 0.10, 1);
  glm::vec3 Cuerpo[12];  // vèrtexs amb X, Y i Z
  
  // minX = -1.0
  // maxX = 0.0
  // minY = -1.0
  // maxY = 0.0
  
  //Rectangulo inferior
  Cuerpo[0] = glm::vec3(-0.55, -0.1, 0);
  Cuerpo[1] = glm::vec3( -0.55, 0.15, 0);
  Cuerpo[2] = glm::vec3( 0.45, -0.1, 0);
  Cuerpo[3] = glm::vec3( 0.45, 0.15, 0);
  Cuerpo[4] = glm::vec3( 0.45, -0.1, 0);
  Cuerpo[5] = glm::vec3( -0.55, 0.15, 0);
  
  //Rectangulo superior
  Cuerpo[6] = glm::vec3( -0.17, 0.4, 0);
  Cuerpo[7] = glm::vec3( -0.17, 0.15, 0);
  Cuerpo[8] = glm::vec3( 0.325, 0.4, 0);
  Cuerpo[9] = glm::vec3( -0.17, 0.15, 0);
  Cuerpo[10] = glm::vec3( 0.325, 0.4, 0);
  Cuerpo[11] = glm::vec3( 0.325, 0.15, 0);

  glm::vec3 ColorCos[12];
  for (int i = 0; i < 12; ++i) ColorCos[i] = glm::vec3(0.2, 0.6, 0.1);

  glm::vec3 Cano[6];
  Cano[0] = glm::vec3(0.07, 0.335, 1);
  Cano[1] = glm::vec3(0.07, 0.215, 1);
  Cano[2] = glm::vec3(0.82, 0.215, 1);
  Cano[3] = glm::vec3(0.82, 0.335, 1);
  Cano[4] = glm::vec3(0.07, 0.335, 1);
  Cano[5] = glm::vec3(0.82, 0.215, 1);

  glm::vec3 ColorCano[6];
  for(int i = 0; i < 6; ++i) ColorCano[i] = glm::vec3(0.5, 0.5, 0.5);

  glm::vec3 Roda[6];
  Roda[0] = glm::vec3(-0.38, -0.08, 1);
  Roda[1] = glm::vec3(-0.38, -0.12, 1);
  Roda[2] = glm::vec3(-0.3, -0.12, 1);
  Roda[3] = glm::vec3(-0.3, -0.12, 1);
  Roda[4] = glm::vec3(-0.3, -0.08, 1);
  Roda[5] = glm::vec3(-0.38, -0.08, 1);
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar el quadrat
  glGenVertexArrays(3, VAO);
  //VAO Cuadrat
  glBindVertexArray(VAO[0]);

  // Creació del buffer amb les posicions dels vèrtexs
  GLuint VBO[10];
  glGenBuffers(10, VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Cuerpo), Cuerpo, GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(ColorCos), ColorCos, GL_STATIC_DRAW);
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  // VAO Cano
  glBindVertexArray(VAO[1]);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Cano), Cano, GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(ColorCano), ColorCano, GL_STATIC_DRAW);
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  //VAO Roda
  glBindVertexArray(VAO[2]);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Roda), Roda, GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(ColorCano), ColorCano, GL_STATIC_DRAW);
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);
}


void MyGLWidget::carregaShaders()
{
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
  colorLoc = glGetAttribLocation (program->programId(), "color");
  
  // Obtenim els identificadors dels uniforms
  TGLoc = glGetUniformLocation(program->programId(), "TG"); 
}

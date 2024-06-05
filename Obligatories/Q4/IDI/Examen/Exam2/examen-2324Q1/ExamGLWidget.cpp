#include "ExamGLWidget.h"

#include <iostream>

ExamGLWidget::ExamGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  setFocusPolicy(Qt::StrongFocus); // per rebre events de teclat
  xClick = yClick = 0;
  DoingInteractive = NONE;
}

ExamGLWidget::~ExamGLWidget() {
  if (program != NULL)
    delete program;
}

void ExamGLWidget::initializeGL() {
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  carregaShaders();
  iniEscena();
  iniCamera();
}

void ExamGLWidget::iniEscena() {
  creaBuffersModels();

  // inicialitzem tots els possibles objectes (blocs de Lego) com a "buits" -->
  // no es pinten ni tenen valors guardats més que els per defecte
  for (int i = 0; i < NUM_BRICKS; i++) {
    pintarBricks[i] = false;
    brickModelIndex[i] = 1;
    brickTGs[i] = glm::mat4(1);
    brickColors[i] = glm::vec3(1, 1, 1);
  }

  // inicialitzem l'objecte actual (el bloc de Lego) a editar
  currentBrickObjectIndex = 0;
  currentBrickModelIndex = 1;

  // inicialitzem el color actual
  currentColor = white;

  // Inicialitzem els paràmetres de l'escena amb valors arbitraris
  centreEsc = glm::vec3(0, 2.0, 0);
  radiEsc = 10;
}

void ExamGLWidget::iniCamera() {
  // Inicialitzem els paràmetres de càmera amb valors arbitraris
  angleY = M_PI / 4.0f;
  ra = float(width()) / height();
  fov = float(M_PI / 3.0);
  zn = 15;
  zf = 65;

  projectTransform();
  viewTransform();
}

void ExamGLWidget::paintGL() {
  // En cas de voler canviar els paràmetres del viewport, descomenteu la crida
  // següent i useu els paràmetres que considereu (els que hi ha són els de per
  // defecte)
  //  glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer i el depth-buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra = GROUND_BRICKS
  glUniform3fv(colorLoc, 1, &white[0]);
  glBindVertexArray(VAO_models[GROUND_BRICKS]);
  modelTransformGround();
  glDrawArrays(GL_TRIANGLES, 0, models[GROUND_BRICKS].faces().size() * 3);

  // Pintem el bloc de Lego actual (currentBrick) del color actual
  glUniform3fv(colorLoc, 1, &currentColor[0]);
  glBindVertexArray(VAO_models[currentBrickModelIndex]);
  modelTransformCurrentBrick();
  glDrawArrays(GL_TRIANGLES, 0,
               models[currentBrickModelIndex].faces().size() * 3);

  glBindVertexArray(0);
}

void ExamGLWidget::resizeGL(int w, int h) {
#ifdef __APPLE__
  // Aquest codi és necessari únicament per a MACs amb pantalla retina.
  GLint vp[4];
  glGetIntegerv(GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif

  ra = float(ample) / float(alt);
  projectTransform();
}

void ExamGLWidget::modelTransformGround() {
  glm::mat4 TG(1.f);
  TG = glm::translate(TG, glm::vec3(0, -0.75f, 0));
  TG = glm::scale(TG, glm::vec3(escalaModels[GROUND_BRICKS],
                                escalaModels[GROUND_BRICKS],
                                escalaModels[GROUND_BRICKS]));
  TG = glm::translate(TG, -centreCapsaModels[GROUND_BRICKS]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void ExamGLWidget::modelTransformBrick(int brickIndex) {
  glm::mat4 TG = brickTGs[brickIndex];
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void ExamGLWidget::modelTransformCurrentBrick() {
  glm::mat4 TG(1.f);
  TG = glm::translate(TG, glm::vec3(0, 2.5, 0));
  TG = glm::scale(TG, glm::vec3(escalaModels[currentBrickModelIndex],
                                escalaModels[currentBrickModelIndex],
                                escalaModels[currentBrickModelIndex]));
  TG = glm::translate(TG, -centreCapsaModels[currentBrickModelIndex]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void ExamGLWidget::projectTransform() {
  glm::mat4 Proj; // Matriu de projecció
  Proj = glm::perspective(fov, ra, zn, zf);

  glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void ExamGLWidget::viewTransform() {
  View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2 * radiEsc));
  View = glm::rotate(View, -angleY, glm::vec3(0, 1, 0));
  View = glm::translate(View, -centreEsc);

  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
}

void ExamGLWidget::keyPressEvent(QKeyEvent *event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_M: { // al prèmer la tecla M canviem el model del bloc que estem
                    // editant
    currentBrickModelIndex++;
    if (currentBrickModelIndex == NUM_MODELS)
      currentBrickModelIndex = 1;
    break;
  }
  case Qt::Key_B: { // al prèmer la tecla B canviem el color del bloc que estem
                    // editant
    if (currentColor == white)
      currentColor = glm::vec3(0, 0, 1);
    else
      currentColor = white;
    break;
  }
  default:
    event->ignore();
    break;
  }
  update();
}

void ExamGLWidget::mousePressEvent(QMouseEvent *e) {
  xClick = e->x();
  yClick = e->y();

  if (e->button() & Qt::LeftButton &&
      !(e->modifiers() &
        (Qt::ShiftModifier | Qt::AltModifier | Qt::ControlModifier))) {
    DoingInteractive = ROTATE;
  }
}

void ExamGLWidget::mouseReleaseEvent(QMouseEvent *) { DoingInteractive = NONE; }

void ExamGLWidget::mouseMoveEvent(QMouseEvent *e) {
  makeCurrent();
  if (DoingInteractive == ROTATE) {
    // Fem la rotació (només en Y)
    angleY += (e->x() - xClick) * M_PI / ample;
    viewTransform();
  }

  xClick = e->x();
  yClick = e->y();

  update();
}

void ExamGLWidget::calculaCapsaModel(Model &p, float &escala,
                                     float ampladaDesitjada,
                                     glm::vec3 &centreCapsa) {
  // Càlcul capsa contenidora i valors transformacions inicials
  float minx, miny, minz, maxx, maxy, maxz;
  minx = maxx = p.vertices()[0];
  miny = maxy = p.vertices()[1];
  minz = maxz = p.vertices()[2];
  for (unsigned int i = 3; i < p.vertices().size(); i += 3) {
    if (p.vertices()[i + 0] < minx)
      minx = p.vertices()[i + 0];
    if (p.vertices()[i + 0] > maxx)
      maxx = p.vertices()[i + 0];
    if (p.vertices()[i + 1] < miny)
      miny = p.vertices()[i + 1];
    if (p.vertices()[i + 1] > maxy)
      maxy = p.vertices()[i + 1];
    if (p.vertices()[i + 2] < minz)
      minz = p.vertices()[i + 2];
    if (p.vertices()[i + 2] > maxz)
      maxz = p.vertices()[i + 2];
  }
  escala = ampladaDesitjada / (maxx - minx);
  centreCapsa = glm::vec3((minx + maxx) / 2.0f, (miny + maxy) / 2.0f,
                          (minz + maxz) / 2.0f);
}

void ExamGLWidget::creaBuffersModels() {
  // Creació de VAOs i VBOs per pintar els models
  glGenVertexArrays(NUM_MODELS, &VAO_models[0]);

  for (int i = 0; i < NUM_MODELS; i++) {
    // Càrrega del models
    models[i].load("./models/" + objNames[i]);

    // Calculem la capsa contenidora del model
    calculaCapsaModel(models[i], escalaModels[i], ampladesDesitjades[i],
                      centreCapsaModels[i]);

    glBindVertexArray(VAO_models[i]);

    // Creació dels buffers del model fantasma
    GLuint VBO[6];
    // Buffer de posicions
    glGenBuffers(6, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * models[i].faces().size() * 3 * 3,
                 models[i].VBO_vertices(), GL_STATIC_DRAW);

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    // Buffer de normals
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * models[i].faces().size() * 3 * 3,
                 models[i].VBO_normals(), GL_STATIC_DRAW);

    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(normalLoc);

    // En lloc del color, ara passem tots els paràmetres dels materials
    // Buffer de component ambient
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * models[i].faces().size() * 3 * 3,
                 models[i].VBO_matamb(), GL_STATIC_DRAW);

    glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(matambLoc);

    // Buffer de component difusa
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * models[i].faces().size() * 3 * 3,
                 models[i].VBO_matdiff(), GL_STATIC_DRAW);

    glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(matdiffLoc);

    // Buffer de component especular
    glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * models[i].faces().size() * 3 * 3,
                 models[i].VBO_matspec(), GL_STATIC_DRAW);

    glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(matspecLoc);

    // Buffer de component shininness
    glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * models[i].faces().size() * 3,
                 models[i].VBO_matshin(), GL_STATIC_DRAW);

    glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(matshinLoc);
  }

  glBindVertexArray(0);
}

void ExamGLWidget::carregaShaders() {
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs(QOpenGLShader::Fragment, this);
  QOpenGLShader vs(QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("./shaders/basicLlumShader.frag");
  vs.compileSourceFile("./shaders/basicLlumShader.vert");
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
  vertexLoc = glGetAttribLocation(program->programId(), "vertex");
  // Obtenim identificador per a l'atribut “normal” del vertex shader
  normalLoc = glGetAttribLocation(program->programId(), "normal");
  // Obtenim identificador per a l'atribut “matamb” del vertex shader
  matambLoc = glGetAttribLocation(program->programId(), "matamb");
  // Obtenim identificador per a l'atribut “matdiff” del vertex shader
  matdiffLoc = glGetAttribLocation(program->programId(), "matdiff");
  // Obtenim identificador per a l'atribut “matspec” del vertex shader
  matspecLoc = glGetAttribLocation(program->programId(), "matspec");
  // Obtenim identificador per a l'atribut “matshin” del vertex shader
  matshinLoc = glGetAttribLocation(program->programId(), "matshin");

  // Demanem identificadors per als uniforms dels shaders
  transLoc = glGetUniformLocation(program->programId(), "TG");
  projLoc = glGetUniformLocation(program->programId(), "proj");
  viewLoc = glGetUniformLocation(program->programId(), "view");
  colorLoc = glGetUniformLocation(program->programId(), "colorMul");
}

// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__, __FUNCTION__)
#define DEBUG()                                                                \
  std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) {
  GLenum glErr;
  int retCode = 0;

  glErr = glGetError();
  const char *error = 0;
  switch (glErr) {
  case 0x0500:
    error = "GL_INVALID_ENUM";
    break;
  case 0x501:
    error = "GL_INVALID_VALUE";
    break;
  case 0x502:
    error = "GL_INVALID_OPERATION";
    break;
  case 0x503:
    error = "GL_STACK_OVERFLOW";
    break;
  case 0x504:
    error = "GL_STACK_UNDERFLOW";
    break;
  case 0x505:
    error = "GL_OUT_OF_MEMORY";
    break;
  default:
    error = "unknown error!";
  }
  if (glErr != GL_NO_ERROR) {
    printf("glError in file %s @ line %d: %s function: %s\n", file, line, error,
           func);
    retCode = 1;
  }
  return retCode;
}

MyGLWidget::MyGLWidget(QWidget *parent) : ExamGLWidget(parent) {}

MyGLWidget::~MyGLWidget() {}

void MyGLWidget::iniEscena() {
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
  centreEsc = glm::vec3(0, 4.375, 0);
  radiEsc = 15.13;
  x = y = z = 0;
  angleRotacio = 0;
  camPlanta = false;
  indexBrick = 0;
}

void MyGLWidget::iniCamera() {
  // Inicialitzem els paràmetres de càmera amb valors arbitraris
  angleY = M_PI / 12.0f;
  angleX = M_PI / 12.0f;
  ra = float(width()) / height();
  fov = float(M_PI / 3.0);
  zn = radiEsc;
  zf = 3 * radiEsc;

  projectTransform();
  viewTransform();
}

void MyGLWidget::reset() {
  for (int i = 0; i < NUM_BRICKS; i++) {
    pintarBricks[i] = false;
    brickModelIndex[i] = 1;
    brickTGs[i] = glm::mat4(1);
    brickColors[i] = glm::vec3(1, 1, 1);
  }

  x = y = z = 0;
  angleRotacio = 0;
  camPlanta = false;
  indexBrick = 0;
  angleY = M_PI / 12.0f;
  angleX = M_PI / 12.0f;
  currentBrickObjectIndex = 0;
  currentBrickModelIndex = 1;
  currentColor = white;
}

void MyGLWidget::paintGL() {
  // En cas de voler canviar els paràmetres del viewport, descomenteu la crida
  // següent i
  // useu els paràmetres que considereu (els que hi ha són els de per defecte)
  //  glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer i el depth-buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra = GROUND_BRICKS
  glUniform3fv(colorLoc, 1, &red[0]);
  glBindVertexArray(VAO_models[GROUND_BRICKS]);
  modelTransformGround();
  glDrawArrays(GL_TRIANGLES, 0, models[GROUND_BRICKS].faces().size() * 3);

  for (int i = 0; i < indexBrick; ++i) {
    if (pintarBricks[i]) {
      glUniform3fv(colorLoc, 1, &brickColors[i][0]);
      glBindVertexArray(VAO_models[brickModelIndex[i]]);
      glUniformMatrix4fv(transLoc, 1, GL_FALSE, &brickTGs[i][0][0]);
      glDrawArrays(GL_TRIANGLES, 0,
                   models[brickModelIndex[i]].faces().size() * 3);
      glDrawArrays(GL_LINES, 0, models[brickModelIndex[i]].faces().size() * 3);
    }
  }

  // Pintem el bloc de Lego actual (currentBrick) del color actual
  glUniform3fv(colorLoc, 1, &currentColor[0]);
  glBindVertexArray(VAO_models[currentBrickModelIndex]);
  modelTransformCurrentBrick();
  glDrawArrays(GL_TRIANGLES, 0,
               models[currentBrickModelIndex].faces().size() * 3);
  glDrawArrays(GL_LINES, 0, models[currentBrickModelIndex].faces().size() * 3);

  glBindVertexArray(0);
}

void MyGLWidget::modelTransformCurrentBrick() {
  TG = glm::mat4(1.f);
  TG = glm::translate(TG, glm::vec3(x, y, z));
  TG = glm::translate(TG, glm::vec3(0, 2.5, 0));
  // Posar en posicio el bloc 1x2
  if (currentBrickModelIndex == 1)
    TG = glm::translate(TG, glm::vec3(0.5, 0, 0));
  // Fer que es vegi be el bloc quan el rotem 90 graus
  if (angleRotacio == 90 and currentBrickModelIndex == 1)
    TG = glm::translate(TG, glm::vec3(-0.5, 0, 0.5));
  TG = glm::translate(TG, glm::vec3(0, -2.5, 0));
  TG = glm::rotate(TG, glm::radians(angleRotacio), glm::vec3(0, 1, 0));
  TG = glm::rotate(TG, glm::radians(90.0f), glm::vec3(1, 0, 0));
  TG = glm::scale(TG, glm::vec3(escalaModels[currentBrickModelIndex],
                                escalaModels[currentBrickModelIndex],
                                escalaModels[currentBrickModelIndex]));
  TG = glm::translate(TG, -centreCapsaModels[currentBrickModelIndex]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform() {
  View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2 * radiEsc));
  View = glm::rotate(View, angleX, glm::vec3(1, 0, 0));
  View = glm::rotate(View, -angleY, glm::vec3(0, 1, 0));
  View = glm::translate(View, -centreEsc);

  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::projectTransform() {
  glm::mat4 Proj; // Matriu de projecció
  if (!camPlanta) {
    Proj = glm::perspective(fov, ra, zn, zf);
  } else {
    Proj = glm::ortho(-radiEsc, radiEsc, -radiEsc, radiEsc, zn, zf);
  }

  glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent *event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_A: {
    if (x > -10)
      x -= 1;
    paintGL();
    break;
  }
  case Qt::Key_D: {
    if (x < 9)
      x += 1;
    paintGL();
    break;
  }
  case Qt::Key_W: {
    if (z > -9)
      z -= 1;
    paintGL();
    break;
  }
  case Qt::Key_S: {
    if (z < 9)
      z += 1;
    paintGL();
    break;
  }
  case Qt::Key_Up: {
    if (y < 9)
      y += 1;
    paintGL();
    break;
  }
  case Qt::Key_Down: {
    if (y > 0)
      y -= 1;
    paintGL();
    break;
  }
  case Qt::Key_Q: {
    angleRotacio = float(int(angleRotacio + 90) % 180);
    break;
  }
  case Qt::Key_C: {
    camPlanta = !camPlanta;
    projectTransform();
    break;
  }
  case Qt::Key_Space: {
    if (indexBrick < NUM_BRICKS - 1) {
      pintarBricks[indexBrick] = true;
      brickModelIndex[indexBrick] = currentBrickModelIndex;
      brickTGs[indexBrick] = TG;
      brickColors[indexBrick] = currentColor;
    }
    ++indexBrick;
    break;
  }
  case Qt::Key_R: {
    reset();
    break;
  }
  case Qt::Key_B: {
    break;
  }
  default:
    ExamGLWidget::keyPressEvent(event);
    break;
  }

  update();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e) {
  makeCurrent();
  if (DoingInteractive == ROTATE) {
    // Fem la rotació (només en Y)
    angleY += (e->x() - xClick) * M_PI / ample;
    angleX += (e->y() - yClick) * M_PI / ample;
    viewTransform();
  }

  xClick = e->x();
  yClick = e->y();

  update();
}

void MyGLWidget::changeColor(int index) {
  makeCurrent();
  switch (index) {
  case 1:
    currentColor = glm::vec3(1, 0, 0);
    break;
  case 2:
    currentColor = glm::vec3(0, 0, 1);
    break;
  case 3:
    currentColor = glm::vec3(0, 1, 0);
    break;
  case 4:
    currentColor = glm::vec3(0, 1, 1);
    break;
  case 5:
    currentColor = glm::vec3(1, 0, 1);
    break;
  case 6:
    currentColor = glm::vec3(1, 1, 0);
    break;
  case 7:
    currentColor = glm::vec3(0, 0, 0);
    break;
  default:
    currentColor = glm::vec3(1, 1, 1);
    break;
  }
  update();
}

void MyGLWidget::brick1Pressed() {
  makeCurrent();
  currentBrickModelIndex = 1;
  update();
}

void MyGLWidget::brick2Pressed() {
  makeCurrent();
  currentBrickModelIndex = 2;
  update();
}

void MyGLWidget::brick3Pressed() {
  makeCurrent();
  currentBrickModelIndex = 3;
  update();
}
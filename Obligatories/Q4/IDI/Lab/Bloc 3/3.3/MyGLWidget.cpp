// MyGLWidget.cpp
#include "MyGLWidget.h"
#include "glm/gtc/matrix_inverse.hpp"
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

MyGLWidget::~MyGLWidget() {}

void MyGLWidget::iniMaterialTerra() {
  // Donem valors al material del terra
  amb = glm::vec3(0.2, 0.2, 0.2);
  diff = glm::vec3(0.0, 0.0, 0.8);
  spec = glm::vec3(0.75, 0.75, 0.75);
  shin = 100;
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e) {
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE) {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    angleX += (e->y() - yClick) * M_PI / ample;
    MyviewTransform();
  }

  xClick = e->x();
  yClick = e->y();

  update();
}

void MyGLWidget::MyviewTransform() {
  View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2 * radiEsc));
  View = glm::rotate(View, angleX, glm::vec3(1, 0, 0));
  View = glm::rotate(View, -angleY, glm::vec3(0, 1, 0));

  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::modelTransformPatricio() {
  // TG = glm::scale(glm::mat4(1.f), glm::vec3(0.3, 0.3, 0.3));
  TG = glm::translate(TG, posPat);
  TG = glm::scale(
      TG, glm::vec3(escala / 2 * 0.3, escala / 2 * 0.3, escala / 2 * 0.3));
  TG = glm::translate(TG, -centrePatr);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent *event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_O:
    perspectiva = !perspectiva;
    BL3GLWidget::projectTransform();
    break;

  case Qt::Key_1:
    llum_ambient = !llum_ambient;
    glUniform1i(llum_ambLoc, llum_ambient);
    break;

  case Qt::Key_2:
    llum_camara = !llum_camara;
    glUniform1i(llum_camLoc, llum_camara);
    break;

  case Qt::Key_Up:
    if (posFocusA.z > -1 + 0.075) {
      posFocusA.z -= 0.025;
      posPat.z -= 0.025;
      modelTransformPatricio();
    }
    break;

  case Qt::Key_Down:
    if (posFocusA.z < 1 - 0.075) {
      posFocusA.z += 0.025;
      posPat.z += 0.025;
      modelTransformPatricio();
    }
    break;

  case Qt::Key_Left:
    if (posFocusA.x > -1 + 0.075) {
      posFocusA.x -= 0.025;
      posPat.x -= 0.025;
      modelTransformPatricio();
    }
    break;

  case Qt::Key_Right:
    if (posFocusA.x < 1 - 0.075) {
      posFocusA.x += 0.025;
      posPat.x += 0.025;
      modelTransformPatricio();
    }
    break;

  case Qt::Key_B:
    backFace = !backFace;
    if (backFace == 1)
      glEnable(GL_CULL_FACE);
    else
      glDisable(GL_CULL_FACE);
    break;

  default:
    BL3GLWidget::keyPressEvent(event);
    break;
  }
  glUniform3fv(posFocusALoc, 1, &posFocusA[0]);
  update();
}

void MyGLWidget::initializeGL() {
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  carregaShaders();
  posFocusALoc = glGetUniformLocation(program->programId(), "posFocusA");
  posFocusCLoc = glGetUniformLocation(program->programId(), "posFocusC");
  colFocusLocA = glGetUniformLocation(program->programId(), "colorFocusA");
  colFocusLocC = glGetUniformLocation(program->programId(), "colorFocusC");
  focusCamLoc = glGetUniformLocation(program->programId(), "focusCamara");
  llum_camLoc = glGetUniformLocation(program->programId(), "llum_camara");
  llum_ambLoc = glGetUniformLocation(program->programId(), "llum_ambient");

  posFocusA = glm::vec3(0.0, -0.5, 0.0);
  posFocusC = glm::vec3(0.0, 0.0, 0.0);
  colFocusA = glm::vec3(0.6, 0.6, 0.6);
  colFocusC = glm::vec3(0.6, 0.6, 0.0);
  posPat = glm::vec3(0.0, -0.85, 0.0);

  glUniform3fv(posFocusALoc, 1, &posFocusA[0]);
  glUniform3fv(posFocusCLoc, 1, &posFocusC[0]);
  glUniform3fv(colFocusLocA, 1, &colFocusA[0]);
  glUniform3fv(colFocusLocC, 1, &colFocusC[0]);
  glUniform1i(focusCamLoc, camara);
  glUniform1i(llum_camLoc, llum_camara);
  glUniform1i(llum_ambLoc, llum_ambient);

  creaBuffersPatricio();
  creaBuffersTerraIParet();

  iniEscena();
  iniCamera();
}

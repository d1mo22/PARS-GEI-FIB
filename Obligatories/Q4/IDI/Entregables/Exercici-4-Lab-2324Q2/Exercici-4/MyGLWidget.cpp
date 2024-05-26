// MyGLWidget.cpp
#include "MyGLWidget.h"
#include "glm/gtc/matrix_inverse.hpp"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__, __FUNCTION__)
#define DEBUG()                                                                \
  std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

MyGLWidget::MyGLWidget(QWidget *parent) : LL4GLWidget(parent) {}

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

void MyGLWidget::keyPressEvent(QKeyEvent *event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_Up: {
    angleCar1 += 2;
    angleCar2 += 3;
    paintGL();
    break;
  }
  case Qt::Key_L: {
    camara = !camara;
    if (!camara) {
      colCam = glm::vec3(0.0, 0.0, 0.0);
      glClearColor(0.3, 0.3, 0.3, 1.0);
    } else {
      colCam = glm::vec3(0.8, 0.8, 0.8);
      glClearColor(0.5, 0.7, 1.0, 1.0);
    }
    glUniform3fv(colCamLoc, 1, &colCam[0]);
    glUniform1i(camaraLoc, camara);
    break;
  }
  case Qt::Key_S: {
    timer = !timer;
    if (timer) {
      t.start(50);
      connect(&t, &QTimer::timeout, [this]() {
        angleCar1 += 2;
        angleCar2 += 3;
        update();
      });
    } else {
      t.stop();
    }
    break;
  }
  default:
    LL4GLWidget::keyPressEvent(event);
    break;
  }
  update();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e) {
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE) {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    angleX += (e->y() - yClick) * M_PI / ample;
    viewTransform();
  }

  xClick = e->x();
  yClick = e->y();

  update();
}

void MyGLWidget::iniCamera() {
  angleY = 0.0;
  angleX = float(M_PI / 4);

  fov = 2 * asin(float(radiEsc / 2 * radiEsc));

  viewTransform();
}

void MyGLWidget::iniEscena() {
  radiEsc = (5 * sqrt(51)) / 2;
  centreEscena = glm::vec3(0, 2.5, 0);
  angleCar1 = 0.0;
  angleCar2 = 0.0;
}

void MyGLWidget::initializeGL() {
  LL4GLWidget::initializeGL();

  carLoc = glGetUniformLocation(program->programId(), "car");
  camaraLoc = glGetUniformLocation(program->programId(), "camara");
  colCamLoc = glGetUniformLocation(program->programId(), "colCam");
  posFocusCamLoc = glGetUniformLocation(program->programId(), "posFocusCam");
  posFocusCar1Loc = glGetUniformLocation(program->programId(), "posFocusCar1");
  posFocusCar2Loc = glGetUniformLocation(program->programId(), "posFocusCar2");
  posFocusCam = glm::vec3(0.0, 0.0, 0.0);
  colCam = glm::vec3(0.8, 0.8, 0.8);
  camara = true;

  glUniform3fv(posFocusCamLoc, 1, &posFocusCam[0]);
  glUniform3fv(colCamLoc, 1, &colCam[0]);
  glUniform1i(camaraLoc, camara);
  glUniform1i(carLoc, 0);

  calculaPosFocus1();
  calculaPosFocus2();
}

void MyGLWidget::iniMaterialTerra() {
  // Donem valors al material del terra
  amb = glm::vec3(0.0, 0.1, 0.1);
  diff = glm::vec3(0.0, 0.5, 0.5);
  spec = glm::vec3(0.8, 0.8, 0.8);
  shin = 100;
}

void MyGLWidget::viewTransform() {
  View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2 * radiEsc));
  View = glm::rotate(View, angleX, glm::vec3(1, 0, 0));
  View = glm::rotate(View, -angleY, glm::vec3(0, 1, 0));
  View = glm::translate(View, -centreEsc);
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);

  calculaPosFocus1();
  calculaPosFocus2();
}

void MyGLWidget::projectTransform() {
  glm::mat4 Proj; // Matriu de projecció
  Proj = glm::perspective(fov, ra, radiEsc, 3.0f * radiEsc);

  glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::modelTransformRoad(glm::vec3 pos, float angle) {
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, pos);
  TG = glm::rotate(TG, angle, glm::vec3(0, 1, 0));
  TG = glm::scale(TG, glm::vec3(5, 5, 5));
  TG = glm::scale(TG, glm::vec3(escalaModels[ROAD]));
  TG = glm::translate(TG, -centreBaseModels[ROAD]);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformPipe() {
  glm::mat4 TG(1.0f);
  TG = glm::scale(TG, glm::vec3(5, 5, 5));
  TG = glm::translate(TG, glm::vec3(0, 0, 0));
  TG = glm::scale(TG, glm::vec3(escalaModels[PIPE]));
  TG = glm::translate(TG, -centreBaseModels[PIPE]);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformCar1() {
  glm::mat4 TG(1.0f);
  TG = glm::rotate(TG, glm::radians(angleCar1), glm::vec3(0, 1, 0));
  TG = glm::translate(TG, glm::vec3(6.5f, 0, 0));
  TG = glm::scale(TG, glm::vec3(escalaModels[CAR]));
  TG = glm::translate(TG, -centreBaseModels[CAR]);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
  calculaPosFocus1();
}

void MyGLWidget::modelTransformCar2() {
  glm::mat4 TG(1.0f);
  TG = glm::rotate(TG, glm::radians(angleCar2), glm::vec3(0, 1, 0));
  TG = glm::translate(TG, glm::vec3(9.0f, 0, 0));
  TG = glm::scale(TG, glm::vec3(escalaModels[CAR]));
  TG = glm::translate(TG, -centreBaseModels[CAR]);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
  calculaPosFocus2();
}

void MyGLWidget::modelTransformTerra() {
  glm::mat4 TG(1.0f);
  TG = glm::scale(TG, glm::vec3(2.5, 2.5, 2.5));
  TG = glm::translate(TG, glm::vec3(-5, 0, -5));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::paintGL() {
  // En cas de voler canviar els paràmetres del viewport, descomenteu la crida
  // següent i useu els paràmetres que considereu (els que hi ha són els de per
  // defecte) glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer i el depth-buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // TERRA
  glBindVertexArray(VAO_Terra);
  modelTransformTerra();
  glDrawArrays(GL_TRIANGLES, 0, 6);

  // Road
  for (int i = 0; i < 4; ++i) {
    glBindVertexArray(VAO_models[ROAD]);
    switch (i) {
    case 0:
      modelTransformRoad(glm::vec3(5, 0.01, -5), 0.0f);
      break;
    case 1:
      modelTransformRoad(glm::vec3(-5, 0.01, -5), float(M_PI / 2));
      break;
    case 2:
      modelTransformRoad(glm::vec3(-5, 0.01, 5), float(M_PI));
      break;
    case 3:
      modelTransformRoad(glm::vec3(5, 0.01, 5), -float(M_PI / 2));
      break;
    }
    glDrawArrays(GL_TRIANGLES, 0, models[ROAD].faces().size() * 3);
  }

  // Car1
  glBindVertexArray(VAO_models[CAR]);

  glUniform1i(carLoc, 1);
  modelTransformCar1();
  glDrawArrays(GL_TRIANGLES, 0, models[CAR].faces().size() * 3);

  // Car2
  glUniform1i(carLoc, 2);
  modelTransformCar2();
  glDrawArrays(GL_TRIANGLES, 0, models[CAR].faces().size() * 3);

  glUniform1i(carLoc, 0);

  //  Pipe
  glBindVertexArray(VAO_models[PIPE]);
  modelTransformPipe();

  glDrawArrays(GL_TRIANGLES, 0, models[PIPE].faces().size() * 3);

  glBindVertexArray(0);
}

void MyGLWidget::calculaPosFocus1() {
  glm::mat4 TG(1.0f);
  TG = glm::rotate(TG, glm::radians(angleCar1), glm::vec3(0, 1, 0));
  TG = glm::translate(TG, glm::vec3(6.5f, 0, 0));
  TG = glm::scale(TG, glm::vec3(escalaModels[CAR]));
  TG = glm::translate(TG, -centreBaseModels[CAR]);

  posFocusCar1 = glm::vec3(2.48, 0.4, -3.2);
  posFocusCar1 = glm::vec3(TG * glm::vec4(posFocusCar1, 1.0));
  glUniform3fv(posFocusCar1Loc, 1, &posFocusCar1[0]);
}

void MyGLWidget::calculaPosFocus2() {
  glm::mat4 TG(1.0f);
  TG = glm::rotate(TG, glm::radians(angleCar2), glm::vec3(0, 1, 0));
  TG = glm::translate(TG, glm::vec3(9.0f, 0, 0));
  TG = glm::scale(TG, glm::vec3(escalaModels[CAR]));
  TG = glm::translate(TG, -centreBaseModels[CAR]);

  posFocusCar2 = glm::vec3(2.48, 0.4, -3.2);
  posFocusCar2 = glm::vec3(TG * glm::vec4(posFocusCar2, 1.0));
  glUniform3fv(posFocusCar2Loc, 1, &posFocusCar2[0]);
}

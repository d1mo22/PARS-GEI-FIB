// MyGLWidget.h
#include "LL4GLWidget.h"
#include <QTimer>

class MyGLWidget : public LL4GLWidget {
  Q_OBJECT
public:
  MyGLWidget(QWidget *parent = 0);
  ~MyGLWidget();

protected:
  virtual void mouseMoveEvent(QMouseEvent *e);
  virtual void keyPressEvent(QKeyEvent *event);
  virtual void viewTransform();
  virtual void modelTransformTerra();
  virtual void modelTransformCar1();
  virtual void modelTransformCar2();
  virtual void modelTransformPipe();
  virtual void modelTransformRoad(glm::vec3 pos, float angle);
  virtual void paintGL();
  virtual void iniMaterialTerra();
  virtual void iniCamera();
  virtual void iniEscena();
  virtual void projectTransform();
  virtual void initializeGL();
  void calculaPosFocus1();
  void calculaPosFocus2();

private:
  int printOglError(const char file[], int line, const char func[]);
  float angleX, angleCar1, angleCar2;
  float fov;
  int camara;
  GLuint carLoc, posFocusCamLoc, camaraLoc, colCamLoc, posFocusCar1Loc,
      posFocusCar2Loc;
  glm::vec3 centreEscena, posFocusCam, posFocusCar1, posFocusCar2, colCam;
  QTimer t;
  int timer = false;
};

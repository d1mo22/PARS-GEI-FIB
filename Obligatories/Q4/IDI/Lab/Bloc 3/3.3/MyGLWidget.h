// MyGLWidget.h
#include "BL3GLWidget.h"

class MyGLWidget : public BL3GLWidget {
  Q_OBJECT

public:
  MyGLWidget(QWidget *parent = 0) : BL3GLWidget(parent) {}
  ~MyGLWidget();

protected:
  virtual void mouseMoveEvent(QMouseEvent *e);
  virtual void keyPressEvent(QKeyEvent *event);
  virtual void iniMaterialTerra();
  virtual void modelTransformPatricio();
  void MyviewTransform();
  void initializeGL();

private:
  float angleX = 0.0;
  GLint camara = false, llum_camara = false, llum_ambient = true,
        backFace = false; // False escena / True camara
  GLuint posFocusALoc, posFocusCLoc, colFocusLocA, colFocusLocC, focusCamLoc,
      llum_camLoc, llum_ambLoc;
  glm::vec3 posFocusA, posFocusC, colFocusA, colFocusC, posPat;
  int printOglError(const char file[], int line, const char func[]);
};

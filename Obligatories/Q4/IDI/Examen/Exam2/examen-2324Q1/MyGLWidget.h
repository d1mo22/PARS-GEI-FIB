#include "ExamGLWidget.h"

class MyGLWidget : public ExamGLWidget {
  Q_OBJECT

public:
  MyGLWidget(QWidget *parent = 0);
  ~MyGLWidget();

protected:
  virtual void paintGL();
  virtual void keyPressEvent(QKeyEvent *event);
  virtual void mouseMoveEvent(QMouseEvent *event);

  virtual void iniEscena();
  virtual void iniCamera();
  virtual void projectTransform();
  virtual void viewTransform();

  virtual void modelTransformCurrentBrick();
  void reset();

public slots:
  void changeColor(int index);
  void brick1Pressed();
  void brick2Pressed();
  void brick3Pressed();

signals:
  void colorChangedS(int index);
  void brick1();
  void brick2();
  void brick3();

private:
  int printOglError(const char file[], int line, const char func[]);
  glm::vec3 red = glm::vec3(0.7, 0, 0);
  glm::mat4 TG;
  float x, y, z, angleRotacio;
  bool camPlanta;
  int indexBrick;
};

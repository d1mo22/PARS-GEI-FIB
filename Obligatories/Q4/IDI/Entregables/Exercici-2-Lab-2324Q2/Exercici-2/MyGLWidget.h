#include "LL2GLWidget.h"

#include <vector>

#include <QTimer>

class MyGLWidget : public LL2GLWidget
{
  Q_OBJECT

public:
  MyGLWidget(QWidget *parent);
  ~MyGLWidget();

protected:
  virtual void keyPressEvent(QKeyEvent *event);

  virtual void TerraTransform();

  virtual void PipeTransform(glm::vec3 pos);

  virtual void MarbleTransform();

  virtual void SnakeHeadTransform();

  virtual void SnakeTailTransform();

  virtual void projectTransform();

  virtual void paintGL();

  virtual void viewTransform();

  virtual void iniCamera();

  virtual void iniEscena();

  // virtual void creaBuffersModels();
  //  funció per comprovar si una nova posició de la serp és vàlida
  virtual bool checkPosition(glm::vec3 pos);

  virtual void mouseMoveEvent(QMouseEvent *e);

  virtual void mouseReleaseEvent(QMouseEvent *);

  virtual void mousePressEvent(QMouseEvent *e);

  virtual void resizeGL(int w, int h);

public slots:

private:
  void drawPipe();

  int printOglError(const char file[], int line, const char func[]);

  float psi = 0.0, theta = float(M_PI) / 4;
  bool prespectiva = true;
  float left, right, bot, top;
};

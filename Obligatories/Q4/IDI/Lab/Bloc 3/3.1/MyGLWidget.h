// MyGLWidget.h
#include "BL3GLWidget.h"

class MyGLWidget : public BL3GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL3GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void iniMaterialTerra();
    void MyviewTransform ();
    void initializeGL ();



  private:
    float angleX = 0.0;
    GLuint posFocusLoc, colFocusLoc;
    glm::vec3 posFocus, colFocus;
    int printOglError(const char file[], int line, const char func[]);
};

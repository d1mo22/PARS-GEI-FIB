#include "LL2GLWidget.h"

#include <vector>

#include <QTimer>

class MyGLWidget : public LL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent);
    ~MyGLWidget();

  protected:
  
    virtual void keyPressEvent (QKeyEvent *event);

    // funció per comprovar si una nova posició de la serp és vàlida
    virtual bool checkPosition(glm::vec3 pos);

  public slots:


  private:
  
    int printOglError(const char file[], int line, const char func[]);
   
};

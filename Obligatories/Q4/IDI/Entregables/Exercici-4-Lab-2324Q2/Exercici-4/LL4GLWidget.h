#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QMouseEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "model.h"

class LL4GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

  public:
    LL4GLWidget (QWidget *parent=0);
    ~LL4GLWidget ();

  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ( );
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ( );
    // resizeGL - És cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);
    // keyPressEvent - Es cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);
    // mouse{Press/Release/Move}Event - Són cridades quan es realitza l'event 
    // corresponent de ratolí
    virtual void mousePressEvent (QMouseEvent *event);
    virtual void mouseReleaseEvent (QMouseEvent *event);

    virtual void iniEscena ();
    virtual void iniCamera ();
    virtual void iniMaterialTerra ();
    virtual void modelTransformTerra ();
    virtual void modelTransformRoad (glm::vec3 pos, float angle);
    virtual void modelTransformPipe ();
    virtual void modelTransformCar (float radi, float angle);

    virtual void viewTransform ();
    void projectTransform ();
    
    void creaBuffersModels ();	
    void creaBuffersTerra ();
    void carregaShaders ();

    // calculaCapsaModel - Calcula la capsa contenidora d'un Model p retornant el centre de la seva base a CentreBase, i el factor d'escala necessari per a que la seva profunditat (z) sigui profunditatDesitjada.
    void calculaCapsaModel (Model &p, float &escala, float profunditatDesitjada, glm::vec3 &CentreBase);

    // enum models - els models estan en un array de VAOs (VAO_models), aquest enum és per fer més llegible el codi. 
    typedef enum { ROAD = 0, PIPE = 1, CAR = 2, NUM_MODELS = 3} ModelType;

    // VAO names
    GLuint VAO_models[NUM_MODELS];
    GLuint VAO_Terra;

    // Program
    QOpenGLShaderProgram *program;

    // Viewport
    GLint ample, alt;

    // uniform locations
    GLuint transLoc, projLoc, viewLoc;
    // attribute locations
    GLuint vertexLoc, normalLoc, matambLoc, matdiffLoc, matspecLoc, matshinLoc;

    // Matriu de posició i orientació
    glm::mat4 View;

    // Models, capses contenidores i escales
    Model models[NUM_MODELS];
    glm::vec3 centreBaseModels[NUM_MODELS];        
    float escalaModels[NUM_MODELS];    

    // paràmetres de l'escena
    glm::vec3 centreEsc;
    float ra, radiEsc;

    // Definim els paràmetres del material del terra
    glm::vec3 amb, diff, spec;
    float shin;

    typedef  enum {NONE, ROTATE} InteractiveAction;
    InteractiveAction DoingInteractive;
    int xClick, yClick;
    float angleY;
    float factorAngleY;
};


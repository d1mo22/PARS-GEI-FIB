#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "model.h"


class LL2GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

  public:
    LL2GLWidget (QWidget *parent=0);
    ~LL2GLWidget ();

  protected:
    // initializeGL - Aqui incluim les inicialitzacions del context gràfic.
    virtual void initializeGL ( );
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ( );
    // resizeGL - És cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);
    // keyPressEvent - És cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);
    // mouse{Press/Release/Move}Event - Són cridades quan es realitza l'event
    // corresponent de ratolí
    virtual void mousePressEvent (QMouseEvent *event);
    virtual void mouseReleaseEvent (QMouseEvent *event);
    virtual void mouseMoveEvent (QMouseEvent *event);

    // iniEscena - Aqui incluim les inicialitzacions de l'escena
    virtual void iniEscena ();
    // iniCamera - Aqui incluim les inicialitzacions de la camera
    virtual void iniCamera ();    
    
    // viewTransform i projecTransform - Es fan servir per construir i enviar als shader les matrius de càmera (View i Projection respectivament).
    virtual void viewTransform ();
    virtual void projectTransform ();
    
    // {SnakeHead/SnakeBody/SnakeTail/Terra}Transform - Funcions per construir i enviar al shader diferents matrius de transformació geomètrica TG
    virtual void SnakeHeadTransform();
    virtual void SnakeBodyTransform(glm::vec3 pos);
    virtual void SnakeTailTransform();
    virtual void MarbleTransform();
    virtual void PipeTransform(glm::vec3 pos);
    virtual void TerraTransform();

    // funció per comprovar si una nova posició de la serp és vàlida
    virtual bool checkPosition(glm::vec3 pos);
    
    // calculaCapsaModel - Calcula la capsa contenidora d'un Model p retornant el centre de la seva base a CentreBase, i el factor d'escala necessari per a que la seva alçada (y) sigui alçadaDesitjada.
    void calculaCapsaModel (Model &p, float &escala, float alcadaDesitjada, glm::vec3 &CentreBase);
    // creaBuffersModels - Carreguem els fitxers obj i fem la inicialització dels diferents VAOS i VBOs
    void creaBuffersModels ();
    // creaBuffersTerra - Inicialitzem el VAO i els VBO d'un model fet a mà que representa un terra
    void creaBuffersTerra ();
    // carregaShaders - Carreguem els shaders, els compilem i els linkem. També busquem els uniform locations que fem servir.
    void carregaShaders ();
    
    // funció per actualitzar l'estat del joc
    void updateSnakeGame();
    // funció que calcula una nova posició aleatoria per la canica que sigui vàlida
    void computeRandomMarblePosition();
    // signedAngleBetweenVectors - retorna l'angle entre dos vectors a i b, amb el signe respecte al vector (0,1,0)
    float signedAngleBetweenVectors(glm::vec3 a, glm::vec3 b);

    // attribute locations
    GLuint vertexLoc, colorLoc;

    // uniform locations
    GLuint transLoc, viewLoc, projLoc;

    // enum models - els models estan en un array de VAOs (VAO_models), aquest enum és per fer més llegible el codi. 
    typedef enum { SNAKE_HEAD = 0, SNAKE_BODY = 1, SNAKE_TAIL = 2, MARBLE = 3, PIPE = 4, NUM_MODELS = 5} ModelType;

    // VAO names
    GLuint VAO_models[NUM_MODELS];
    GLuint VAO_Terra;

    // Program
    QOpenGLShaderProgram *program;

    // Viewport
    GLint ample, alt;

    // Mouse interaction
    typedef  enum {NONE, ROTATE} InteractiveAction;
    InteractiveAction DoingInteractive;
    int xClick, yClick;
    float factorAngleX, factorAngleY;

    // Internal vars
    float radiEscena;
    float fov, ra=1, znear, zfar;
    glm::vec3 centreEscena, obs, vrp, up;

    // Models, capses contenidores i escales
    Model models[NUM_MODELS];
    glm::vec3 centreBaseModels[NUM_MODELS];        
    float escalaModels[NUM_MODELS];        

    // posicions i angles de les parts de la serp
    glm::vec3 headPos;
    float headAngle;
    // cua de posicions per construir el cos de la serp
    std::vector<glm::vec3> bodyPos;
    glm::vec3 tailPos;
    // angle de gir de la cua
    float tailAngle;
    // direcció de moviment de la serp
    glm::vec3 direction;
    
    // posicio de la canica
    glm::vec3 marblePos;
};


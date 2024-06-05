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

// definim el numero total de models a carregar
#define NUM_MODELS 4

// definim el numero màxim de blocs a afegir
#define NUM_BRICKS 50


class ExamGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

  public:
    ExamGLWidget (QWidget *parent=0);
    ~ExamGLWidget ();

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
    virtual void mouseMoveEvent (QMouseEvent *event);

    // model transforms
    virtual void modelTransformGround (); // model transform per pintar el terra de lego (model GROUND_BRICKS)
    virtual void modelTransformBrick (int brickIndex); // model transform per pintar un block ja editat i guardat
    virtual void modelTransformCurrentBrick(); // model transform per pintar el bloc de lego que estem editant per afegir-lo a l'escena

    // iniEscena - mètode per inicialitzar paràmetres que configuren l'escena (com el centre i el radi de l'esfera contenidora)
    virtual void iniEscena ();
    // iniCamera - mètode per inicialitzar paràmetres de càmera 
    virtual void iniCamera ();
    
    // projectTransform - mètode per definir la projection matrix
    virtual void projectTransform ();
    // viewTransform - mètode per definir la view matrix
    virtual void viewTransform ();

    // carregaShaders - mètode que carrega i compila els shaders, i on també busquem attrib locations i uniform locations
    virtual void carregaShaders ();

    // creaBuffersModels - Aquí carreguem els fitxers obj i fem la inicialització dels diferents VAOS i VBOs
    void creaBuffersModels ();    
    // calculaCapsaModel - Calcula la capsa contenidora d'un Model p retornant el centre absolut de la seva capsa contenidora a centreCapsa, i el factor d'escala necessari per a que la seva amplada sigui ampladaDesitjada (dimensió en X desitjada).
    void calculaCapsaModel (Model &p, float &escala, float ampladaDesitjada, glm::vec3 &centreCapsa);


    /***********************************************/
    // Models, VAOS, capses contenidores i escales
    /***********************************************/
    
    // enum models - els models estan en un array de VAOs (VAO_models), aquest enum és per fer més llegible el codi. 
    typedef enum {GROUND_BRICKS = 0, BRICK_1x2 = 1, BRICK_2x2 = 2, BRICK_4x2 = 3} ModelType;    
    
    // Array amb els noms dels fitxers .obj a carregar ordenats com en el enum ModelType	
    std::string objNames[NUM_MODELS] = {"Lego_Ground.obj","Lego_Brick_1x2.obj", "Lego_Brick_2x2.obj", "Lego_Brick_4x2.obj"};	    

    // Array de models carregats
    Model models[NUM_MODELS];
    
    // Array amb els VAOs dels models carregats
    GLuint VAO_models[NUM_MODELS];        
        
    // Array on es guarden els centres de las capses contenidores de tots els models
    glm::vec3 centreCapsaModels[NUM_MODELS];        
    // Array on es  guarden els factors d'escala que s'han d'aplicar a tots els models
    float escalaModels[NUM_MODELS];
    // Array amb les amplades (dimensión en X) que volem que tinguin els models - es fan servir per calcular els valors de escalaModels dins del mètode calculaCapsaModel	
    float ampladesDesitjades[NUM_MODELS] = {20,1,2,4};

    
    /***********************************************/
    
    /***************************************************/
    // Objectes (blocs de LEGO) --> instàncies de model        
    /***************************************************/
        
    // Objectes guardats    
    bool pintarBricks[NUM_BRICKS]; // Array que indica si l'objecte (el bloc de Lego) s'ha de pintar perque ja ha sigut editat i guardat
    int brickModelIndex[NUM_BRICKS]; // Array que indica de quin model són els objectes (quin bloc de LEGO) si s'han de pintar
    glm::mat4 brickTGs[NUM_BRICKS]; // Array on guardar les transformacions geomètriques (TGs) dels objectes que es van editant i guardant
    glm::vec3 brickColors[NUM_BRICKS]; // Array on guardar els colors per pintar els objectes que es van editant i guardant
    
    // Objecte actual (el que estem editant)
    int currentBrickObjectIndex; // Index de l'objete (el bloc de Lego) actual que estem editant i que farem servir per guardar de quin model és, la TG que estem editant i el color escollit
    int currentBrickModelIndex; // Indica de quin model és l'objecte que estem editant (per després guardar-lo a brickModelIndex)

    glm::vec3 currentColor; // Indica de quin color és l'objecte que estem editant

    glm::vec3 white = glm::vec3(1,1,1); // definim el color blanc


        
    /***************************************************/    


    /***************************************************/
    // Shaders
    /***************************************************/
        
    // Program
    QOpenGLShaderProgram *program;
    // uniform locations
    GLuint transLoc, projLoc, viewLoc, colorLoc;
    // attribute locations
    GLuint vertexLoc, normalLoc, matambLoc, matdiffLoc, matspecLoc, matshinLoc;

    /***************************************************/


    /***************************************************/
    // Viewport i Càmera
    /***************************************************/

    GLint ample, alt;     // Resolució del viewport

    glm::mat4 View;     // Matriu de posició i orientació de la càmera
   
    glm::vec3 centreEsc; // centre de l'escena
    float radiEsc, ra, fov, zn, zf; // radi de l'escena, relació d'aspecte, field of view, znear i zfar

    float angleX, angleY; // angles d'Euler per construir la view matrix

    typedef  enum {NONE, ROTATE} InteractiveAction; // enum per diferenciar si estem rotant o no la càmera
    InteractiveAction DoingInteractive;
    int xClick, yClick; // enters per guardar les coordenades on es fa click amb el ratolí quan volem moure la càmera
    
    /***************************************************/

};


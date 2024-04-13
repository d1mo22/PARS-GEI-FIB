#include "LL2GLWidget.h"

#include <iostream>

LL2GLWidget::LL2GLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
  xClick = yClick = 0;
  DoingInteractive = NONE;
}

LL2GLWidget::~LL2GLWidget ()
{
  if (program != NULL)
    delete program;
}

void LL2GLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  
  glEnable(GL_DEPTH_TEST);
  
  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffersModels();
  creaBuffersTerra();
  iniEscena();
  iniCamera();
}

void LL2GLWidget::iniEscena()
{
  radiEscena = sqrt(80);
  centreEscena = glm::vec3(0,0,0);

  headPos = glm::vec3(-5,0,0);
  headAngle = 0;
  bodyPos.clear();	    
  bodyPos.push_back(glm::vec3(-1,0,0));    	
  tailPos = glm::vec3(4,0,0);
  tailAngle = 0;

  marblePos = glm::vec3(10, 0, 0);

  direction = glm::vec3(1,0,0);
}

void LL2GLWidget::iniCamera(){

  obs = glm::vec3(0, 8, -30);
  vrp = glm::vec3(0, -2, 0);
  up = glm::vec3(0, 1, 0);
  fov = float(M_PI)/4.0f;
  znear =  1;
  zfar  = 60;

  viewTransform();
}

void LL2GLWidget::paintGL ()
{
  // descomentar per canviar paràmetres
  // glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // SnakeHead
  glBindVertexArray (VAO_models[SNAKE_HEAD]);
  SnakeHeadTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[SNAKE_HEAD].faces().size()*3);
  
  // SnakeBody
  glBindVertexArray (VAO_models[SNAKE_BODY]);
  for (unsigned int i = 0; i < bodyPos.size(); i++)
  {  
	  SnakeBodyTransform(bodyPos[i]);
	  glDrawArrays(GL_TRIANGLES, 0, models[SNAKE_BODY].faces().size()*3);
  }

  // SnakeTail
  glBindVertexArray (VAO_models[SNAKE_TAIL]);
  SnakeTailTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[SNAKE_TAIL].faces().size()*3);
  
  // Marble
  glBindVertexArray (VAO_models[MARBLE]);
  MarbleTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[MARBLE].faces().size()*3);

  // Pipe
  glBindVertexArray (VAO_models[PIPE]);
  PipeTransform(glm::vec3(-8,0,0));
  glDrawArrays(GL_TRIANGLES, 0, models[PIPE].faces().size()*3);
  
  // Terra
  glBindVertexArray (VAO_Terra);
  TerraTransform();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindVertexArray (0);
}

void LL2GLWidget::SnakeHeadTransform ()
{
  glm::mat4 TG(1.0f);  
  TG = glm::translate(TG, headPos);
  TG = glm::scale(TG, glm::vec3(escalaModels[SNAKE_HEAD]));
  TG = glm::translate(TG, -centreBaseModels[SNAKE_HEAD]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void LL2GLWidget::SnakeBodyTransform (glm::vec3 pos)
{
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, pos);
  TG = glm::scale(TG, glm::vec3(escalaModels[SNAKE_BODY]));
  TG = glm::translate(TG, -centreBaseModels[SNAKE_BODY]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void LL2GLWidget::SnakeTailTransform ()
{
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, tailPos);
  TG = glm::scale(TG, glm::vec3(escalaModels[SNAKE_TAIL]));
  TG = glm::translate(TG, -centreBaseModels[SNAKE_TAIL]);
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void LL2GLWidget::MarbleTransform ()
{
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, marblePos);
  TG = glm::scale(TG, glm::vec3(escalaModels[MARBLE]));
  TG = glm::translate(TG, -centreBaseModels[MARBLE]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void LL2GLWidget::PipeTransform (glm::vec3 pos)
{
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, pos);
  TG = glm::scale(TG, glm::vec3(escalaModels[PIPE]));
  TG = glm::translate(TG, -centreBaseModels[PIPE]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void LL2GLWidget::TerraTransform ()
{
  glm::mat4 TG(1.0f);
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void LL2GLWidget::projectTransform ()
{
  glm::mat4 Proj(1.0f);
  Proj = glm::perspective (fov, ra, znear, zfar);
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void LL2GLWidget::viewTransform ()
{
  // Matriu de posició i orientació de l'observador
  glm::mat4 View(1.0f);
  View = glm::lookAt (obs, vrp, up);
  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void LL2GLWidget::resizeGL (int w, int h) 
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif
  ra = float(ample)/float(alt);
  factorAngleY = M_PI / ample;
  factorAngleX = M_PI / alt;
  projectTransform();
}

bool LL2GLWidget::checkPosition(glm::vec3 pos)
{
	bool valid = true;

        // Aquí cal que completeu el codi de manera adient

	return valid; 
}

void LL2GLWidget::computeRandomMarblePosition()
{
	glm::vec3 newMarblePos = glm::vec3(std::rand()%30-14,0,std::rand()%30-14);
	while (!checkPosition(newMarblePos))
		newMarblePos = glm::vec3(std::rand()%30-14,0,std::rand()%30-14);
	marblePos = newMarblePos;	
}

void LL2GLWidget::updateSnakeGame()
{
	glm::vec3 newPos = headPos + direction;
	
        if (checkPosition(newPos)) // check boundary limits, check if eats himself
	{
		bodyPos.push_back(headPos);	
		headPos = newPos;
		
		if (direction == glm::vec3(0,0,-1))
			headAngle = 90;
		if (direction == glm::vec3(0,0,1))
			headAngle = -90;
		if (direction == glm::vec3(-1,0,0))
			headAngle = 180;
		if (direction == glm::vec3(1,0,0))
			headAngle = 0;			
	
		if (glm::distance(newPos,marblePos) > 0) // check if doesn't eat marble 
		{
			tailPos = bodyPos.front();
			bodyPos.erase(bodyPos.begin());	
			glm::vec3 tailMov = bodyPos.front() - tailPos;
			tailAngle = signedAngleBetweenVectors(glm::vec3(1,0,0),tailMov);
		}
		else
			computeRandomMarblePosition();
	}
}

float LL2GLWidget::signedAngleBetweenVectors(glm::vec3 a, glm::vec3 b)
{
	glm::vec3 na = glm::normalize(a);
	glm::vec3 nb = glm::normalize(b);

	float angle = glm::degrees(glm::acos(glm::dot(na,nb)));
	
	glm::vec3 crossProduct = glm::cross(na,nb);
	glm::vec3 upV = glm::vec3(0,1,0);
	if (glm::dot(upV,crossProduct) < 0) angle = -angle;
	
	return angle;
}

void LL2GLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_Up: { 
      break;
    }
    case Qt::Key_Down: { 
      break;
        }
    case Qt::Key_Left: { 
      break;
        }  
    case Qt::Key_Right: { 
      break;
        }
    case Qt::Key_C: { 
      break;
        }           
    case Qt::Key_R: { 
      break;
        }  
    default: event->ignore(); break;
  }
  update();
}

void LL2GLWidget::mousePressEvent (QMouseEvent *e)
{
  xClick = e->x();
  yClick = e->y();

  if (e->button() & Qt::LeftButton &&
      ! (e->modifiers() & (Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
  {
    DoingInteractive = ROTATE;
  }
}

void LL2GLWidget::mouseReleaseEvent( QMouseEvent *)
{
  DoingInteractive = NONE;
}

void LL2GLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();

  xClick = e->x();
  yClick = e->y();

  update ();
}

void LL2GLWidget::creaBuffersTerra ()
{
  // VBO amb la posició dels vèrtexs
  glm::vec3 posTerra[4] = {
        glm::vec3(-5.0, 0.0, -5.0),
        glm::vec3(-5.0, 0.0,  5.0),
        glm::vec3( 5.0, 0.0, -5.0),
        glm::vec3( 5.0, 0.0,  5.0)
  }; 

  glm::vec3 c(0.65, 0.2, 0.05);
  glm::vec3 colTerra[4] = { c, c, c, c };

  // VAO
  glGenVertexArrays(1, &VAO_Terra);
  glBindVertexArray(VAO_Terra);

  GLuint VBO_Terra[2];
  glGenBuffers(2, VBO_Terra);

  // geometria
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(posTerra), posTerra, GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // color
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colTerra), colTerra, GL_STATIC_DRAW);
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);
  
  glBindVertexArray (0);
}

void LL2GLWidget::calculaCapsaModel (Model &p, float &escala, float alcadaDesitjada, glm::vec3 &centreBase)
{
  // Càlcul capsa contenidora i valors transformacions inicials
  float minx, miny, minz, maxx, maxy, maxz;
  minx = maxx = p.vertices()[0];
  miny = maxy = p.vertices()[1];
  minz = maxz = p.vertices()[2];
  for (unsigned int i = 3; i < p.vertices().size(); i+=3)
  {
    if (p.vertices()[i+0] < minx)
      minx = p.vertices()[i+0];
    if (p.vertices()[i+0] > maxx)
      maxx = p.vertices()[i+0];
    if (p.vertices()[i+1] < miny)
      miny = p.vertices()[i+1];
    if (p.vertices()[i+1] > maxy)
      maxy = p.vertices()[i+1];
    if (p.vertices()[i+2] < minz)
      minz = p.vertices()[i+2];
    if (p.vertices()[i+2] > maxz)
      maxz = p.vertices()[i+2];
  }

  escala = alcadaDesitjada/(maxy-miny);
  centreBase[0] = (minx+maxx)/2.0; centreBase[1] = miny; centreBase[2] = (minz+maxz)/2.0;
}

void LL2GLWidget::creaBuffersModels ()
{
  // Càrrega dels models
  models[SNAKE_HEAD].load("./models/SnakeHead.obj");
  models[SNAKE_BODY].load("./models/SnakeBody.obj");
  models[SNAKE_TAIL].load("./models/SnakeTail.obj");
  models[MARBLE].load("./models/Marble.obj");
  models[PIPE].load("./models/GreenPipe.obj");

  // Creació de VAOs i VBOs per pintar els models
  glGenVertexArrays(NUM_MODELS, &VAO_models[0]);
  
  float alcadaDesitjada[NUM_MODELS] = {1,1,1,1.5,1}; 
  
  for (int i = 0; i < NUM_MODELS; i++)
  {	
	  // Calculem la capsa contenidora del model
	  calculaCapsaModel (models[i], escalaModels[i], alcadaDesitjada[i], centreBaseModels[i]);
  
	  glBindVertexArray(VAO_models[i]);

	  GLuint VBO[2];
	  glGenBuffers(2, VBO);

	  // geometria
	  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*models[i].faces().size()*3*3,
		   models[i].VBO_vertices(), GL_STATIC_DRAW);
	  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	  glEnableVertexAttribArray(vertexLoc);

	  // color
	  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*models[i].faces().size()*3*3,
		   models[i].VBO_matdiff(), GL_STATIC_DRAW);
	  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	  glEnableVertexAttribArray(colorLoc);  
  }
  
  glBindVertexArray (0);
}

void LL2GLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Identificador per als  atributs
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  colorLoc = glGetAttribLocation (program->programId(), "color");

  // Identificadors dels uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");
  projLoc  = glGetUniformLocation (program->programId(), "Proj");
  viewLoc  = glGetUniformLocation (program->programId(), "View");
}


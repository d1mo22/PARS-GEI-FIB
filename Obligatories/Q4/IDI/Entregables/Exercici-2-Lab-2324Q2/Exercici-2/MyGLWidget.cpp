#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__, __FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

MyGLWidget::MyGLWidget(QWidget *parent = 0) : LL2GLWidget(parent)
{
}

int MyGLWidget::printOglError(const char file[], int line, const char func[])
{
  GLenum glErr;
  int retCode = 0;
  glErr = glGetError();
  const char *error = 0;
  switch (glErr)
  {
  case 0x0500:
    error = "GL_INVALID_ENUM";
    break;
  case 0x501:
    error = "GL_INVALID_VALUE";
    break;
  case 0x502:
    error = "GL_INVALID_OPERATION";
    break;
  case 0x503:
    error = "GL_STACK_OVERFLOW";
    break;
  case 0x504:
    error = "GL_STACK_UNDERFLOW";
    break;
  case 0x505:
    error = "GL_OUT_OF_MEMORY";
    break;
  default:
    error = "unknown error!";
  }
  if (glErr != GL_NO_ERROR)
  {
    printf("glError in file %s @ line %d: %s function: %s\n",
           file, line, error, func);
    retCode = 1;
  }
  return retCode;
}

MyGLWidget::~MyGLWidget()
{
}

bool MyGLWidget::checkPosition(glm::vec3 pos)
{
  if (pos.x > 13 || pos.x < -13 || pos.z > 13 || pos.z < -13)
    return false;

  for (int i = 0; i < (int)bodyPos.size(); ++i)
  {
    if (pos.x == bodyPos[i].x and pos.z == bodyPos[i].z)
      return false;
  }

  return true;
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
  makeCurrent();
  switch (event->key())
  {
  case Qt::Key_Up:
  {
    //-Z
    direction = glm::vec3(0, 0, -1);
    updateSnakeGame();
    break;
  }
  case Qt::Key_Down:
  {
    //+Z
    direction = glm::vec3(0, 0, 1);
    updateSnakeGame();
    break;
  }
  case Qt::Key_Left:
  {
    //-X
    direction = glm::vec3(-1, 0, 0);
    updateSnakeGame();
    break;
  }
  case Qt::Key_Right:
  {
    //+X
    direction = glm::vec3(1, 0, 0);
    updateSnakeGame();
    break;
  }
  case Qt::Key_C:
  {
    if (prespectiva)
      prespectiva = false;
    else
      prespectiva = true;
    break;
  }
  case Qt::Key_R:
  {
    iniEscena();
    break;
  }
  default:
    event->ignore();
    break;
  }

  update();
}

void MyGLWidget::mousePressEvent(QMouseEvent *e)
{
  makeCurrent();
  xClick = e->x();
  yClick = e->y();

  if (e->button() & Qt::LeftButton &&
      !(e->modifiers() & (Qt::ShiftModifier | Qt::AltModifier | Qt::ControlModifier)))
  {
    DoingInteractive = ROTATE;
  }
  update();
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent *)
{
  makeCurrent();
  DoingInteractive = NONE;
  update();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  if (DoingInteractive == ROTATE)
  {
    psi += float(M_PI) / 180 * (e->x() - xClick) / 5;
    theta += float(M_PI) / 180 * (e->y() - yClick) / 5;
    xClick = e->x();
    yClick = e->y();
  }
  update();
}

void MyGLWidget::TerraTransform()
{
  glm::mat4 TG(1.0f);
  TG = glm::scale(TG, glm::vec3(3, 1, 3));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::PipeTransform(glm::vec3 pos)
{
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, pos);
  TG = glm::scale(TG, glm::vec3(1, 3, 1));
  TG = glm::scale(TG, glm::vec3(escalaModels[PIPE]));
  TG = glm::translate(TG, -centreBaseModels[PIPE]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::MarbleTransform()
{
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, marblePos);
  TG = glm::scale(TG, glm::vec3(0.5, 0.5, 0.5));
  TG = glm::scale(TG, glm::vec3(escalaModels[MARBLE]));
  TG = glm::translate(TG, -centreBaseModels[MARBLE]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::SnakeHeadTransform()
{
  float angle = headAngle * float(M_PI) / 180;
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, headPos);
  TG = glm::rotate(TG, angle, glm::vec3(0, 1, 0));
  TG = glm::rotate(TG, -float(M_PI) / 2, glm::vec3(0, 1, 0));
  TG = glm::scale(TG, glm::vec3(escalaModels[SNAKE_HEAD]));
  TG = glm::translate(TG, -centreBaseModels[SNAKE_HEAD]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::SnakeTailTransform()
{
  glm::mat4 TG(1.0f);
  float angle = tailAngle * float(M_PI) / 180;
  TG = glm::translate(TG, tailPos);
  TG = glm::rotate(TG, angle, glm::vec3(0, 1, 0));
  TG = glm::scale(TG, glm::vec3(escalaModels[SNAKE_TAIL]));
  TG = glm::translate(TG, -centreBaseModels[SNAKE_TAIL]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::projectTransform()
{
  glm::mat4 Proj(1.0f);
  if (prespectiva)
    Proj = glm::perspective(fov, ra, znear, zfar);
  else
    // Proj = glm::ortho(-radiEscena, radiEscena, -radiEscena, radiEscena, znear, zfar);
    Proj = glm::ortho(left, right, bot, top, znear, zfar);
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform()
{
  glm::mat4 View(1.0f);
  if (prespectiva)
  {
    View = glm::translate(View, glm::vec3(0, 0, -2 * radiEscena));
    View = glm::rotate(View, theta, glm::vec3(1, 0, 0));
    View = glm::rotate(View, psi, glm::vec3(0, 1, 0));
    View = glm::translate(View, glm::vec3(-vrp));
  }
  else
  {
    float i = 0;
    View = glm::translate(View, glm::vec3(0, 0, -2 * radiEscena));
    View = glm::rotate(View, float(M_PI) / 2, glm::vec3(1, 0, 0));
    View = glm::rotate(View, i, glm::vec3(0, 1, 0));
    View = glm::translate(View, glm::vec3(-vrp));
  }

  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::resizeGL(int w, int h)
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv(GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif
  ra = float(ample) / float(alt);

  if (ra > 1)
  {
    left = -radiEscena * ra;
    right = radiEscena * ra;
  }
  else if (ra < 1)
  {
    bot = -radiEscena / ra;
    top = radiEscena / ra;
  }
  factorAngleY = M_PI / ample;
  factorAngleX = M_PI / alt;
  projectTransform();
}

void MyGLWidget::iniEscena()
{
  radiEscena = (3 * sqrt(201)) / 2;
  centreEscena = glm::vec3(0, 1.5, 0);

  prespectiva = true;
  psi = 0.0;
  theta = float(M_PI) / 4;

  headPos = glm::vec3(0, 0, 0);
  headAngle = 0;
  bodyPos.clear();
  bodyPos.push_back(glm::vec3(-1, 0, 0));
  tailPos = glm::vec3(-2, 0, 0);
  tailAngle = 0;

  computeRandomMarblePosition();

  direction = glm::vec3(1, 0, 0);
}

void MyGLWidget::iniCamera()
{
  float d = 2 * radiEscena;
  glm::vec3 u = glm::vec3(0, 0.71, 0.71);

  left = bot = -radiEscena;
  right = top = radiEscena;

  obs = vrp + (d * u);
  vrp = glm::vec3(0, 1.5, 0);
  up = glm::vec3(0, 1, 0);

  fov = 2 * (asin(float(radiEscena / d)));
  znear = radiEscena;
  zfar = 3 * radiEscena;

  viewTransform();
}

void MyGLWidget::drawPipe()
{
  float xx = -14.5;
  float zz = -14.5;
  for (int i = 0; i < 60; ++i)
  {
    if (i == 30)
    {
      xx = -14.5;
      zz = 14.5;
    }
    PipeTransform(glm::vec3(xx, 0, zz));
    glDrawArrays(GL_TRIANGLES, 0, models[PIPE].faces().size() * 3);
    ++xx;
  }
  xx = -14.5;
  zz = -13.5;
  for (int i = 0; i < 56; ++i)
  {
    if (i == 28)
    {
      xx = 14.5;
      zz = -13.5;
    }
    PipeTransform(glm::vec3(xx, 0, zz));
    glDrawArrays(GL_TRIANGLES, 0, models[PIPE].faces().size() * 3);
    ++zz;
  }
}

void MyGLWidget::paintGL()
{
  // descomentar per canviar paràmetres
  // glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  projectTransform();
  viewTransform();

  // SnakeHead
  glBindVertexArray(VAO_models[SNAKE_HEAD]);
  SnakeHeadTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[SNAKE_HEAD].faces().size() * 3);

  // SnakeBody
  glBindVertexArray(VAO_models[SNAKE_BODY]);
  for (unsigned int i = 0; i < bodyPos.size(); i++)
  {
    SnakeBodyTransform(bodyPos[i]);
    glDrawArrays(GL_TRIANGLES, 0, models[SNAKE_BODY].faces().size() * 3);
  }

  // SnakeTail
  glBindVertexArray(VAO_models[SNAKE_TAIL]);
  SnakeTailTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[SNAKE_TAIL].faces().size() * 3);

  // Marble
  glBindVertexArray(VAO_models[MARBLE]);
  MarbleTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[MARBLE].faces().size() * 3);

  // Pipe
  glBindVertexArray(VAO_models[PIPE]);
  drawPipe();

  // Terra
  glBindVertexArray(VAO_Terra);
  TerraTransform();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindVertexArray(0);
}

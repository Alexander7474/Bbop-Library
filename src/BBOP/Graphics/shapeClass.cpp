#include "../../../include/BBOP/Graphics/shapeClass.h"

Shape::Shape(GLfloat* vertices, GLsizeiptr verticesSize, GLuint* indices, GLsizeiptr indicesSize)
  : shapeVBO(vertices, verticesSize, GL_DYNAMIC_DRAW),
    shapeEBO(indices, indicesSize),
    pos(0.0f, 0.0f),
    size(0.0f, 0.0f),
    origin(0.0f, 0.0f),
    RGB(255,255,255),
    shapeCollisionBox(pos, origin, size),
    autoUpdateCollision(true),
    rotation(0.0f),
    alpha(1.0f)
{}

void Shape::setSize(Vector2f nSize)
{
  size = nSize;
  updateVBO();
}

void Shape::setPosition(Vector2f nPos)
{
  pos = nPos;
  updateVBO();
}

void Shape::setOrigin(Vector2f nOrigin)
{
  origin = nOrigin;
  updateVBO();
}

void Shape::setColor(Vector3i nRGB)
{
  RGB = nRGB;
  updateVBORGB();
}

void Shape::setRotation(float nRotation)
{
  rotation = nRotation;
  updateVBO();
}

void Shape::setAlpha(float nAlpha)
{
  alpha = nAlpha;
  updateVBOAlpha();
}

Vector2f Shape::getSize()
{
  return size;
}

Vector2f Shape::getOrigin()
{
  return origin;
}

Vector2f Shape::getPosition()
{
  return pos;
}

Vector3i Shape::getColor()
{
  return RGB;
}

float Shape::getRotation()
{
  return rotation;
}

float Shape::getAlpha()
{
  return alpha;
  updateVBOAlpha();
}

CollisionBox* Shape::getCollisionBox()
{
  return &shapeCollisionBox;
}

void Shape::setAutoUpdateCollision(bool etat)
{
  autoUpdateCollision = etat;
}

RectangleShape::RectangleShape()
  : Shape(vertices, sizeof(vertices), indices, sizeof(indices))
{
  size.x = 50.0f, size.y = 50.0f;
  buildVAO();
}

void RectangleShape::buildVAO()
{
  for(int i = 0; i < 24; i++)
    vertices[i] = 0.0f;
  for(int i = 0; i < 6; i++)
    indices[i] = 0;
  //construtiopn du VAO fontion de la position du rectangle de sa taille et de la taille de la fenetre
  // init coordinate ########################################
   //  vecteur taille de la fenetre
  Vector2f w(BBOP_WINDOW_SIZE.x/2.0f,BBOP_WINDOW_SIZE.y/2.0f);
  // vecteur de position normalisé
  Vector2f posO(pos.x/w.x-1.0f,pos.y/w.y-1.0f);
  // vecteur position normalizé
  Vector2f pTL(-origin.x/w.x, -origin.y/w.y);
  Vector2f pTR(pTL.x+(size.x/w.x),pTL.y);
  Vector2f pBR(pTR.x,pTL.y+(size.y/w.y));
  Vector2f pBL(pTL.x,pBR.y);
  //application de la rotation
  float cosAngle = cos(rotation);
  float sinAngle = sin(rotation);
  pTL = Vector2f(pTL.x * cosAngle - pTL.y*sinAngle,pTL.x*sinAngle+pTL.y*cosAngle);
  pTR = Vector2f(pTR.x * cosAngle - pTR.y*sinAngle,pTR.x*sinAngle+pTR.y*cosAngle);
  pBR = Vector2f(pBR.x * cosAngle - pBR.y*sinAngle,pBR.x*sinAngle+pBR.y*cosAngle);
  pBL = Vector2f(pBL.x * cosAngle - pBL.y*sinAngle,pBL.x*sinAngle+pBL.y*cosAngle);
  //top right
  vertices[0] = pTR.x+posO.x; vertices[1] = -(pTR.y+posO.y);
  //botton right
  vertices[6] = pBR.x+posO.x; vertices[7] = -(pBR.y+posO.y);
  //bottom left
  vertices[12] = pBL.x+posO.x; vertices[13] = -(pBL.y+posO.y);
  //top left
  vertices[18] = pTL.x+posO.x; vertices[19] = -(pTL.y+posO.y);
 
  // color change ########################################
  float r = RGB.x/255.0f;float g = RGB.y/255.0f;float b = RGB.z/255.0f;
  for(int i = 0; i < 24;i+=6){
    vertices[i+2] = r;vertices[i+3] = g; vertices[i+4] = b;vertices[i+5] = alpha;
  }
  indices[0] = 0;indices[1] = 1;indices[2] = 3;indices[3] = 1;indices[4] = 2;indices[5] = 3;
  shapeVAO.Bind(); 
  shapeVBO.update(vertices, sizeof(vertices));
  shapeEBO.update(indices, sizeof(indices));
  shapeVAO.LinkVBO(shapeVBO, 0, 2, 6, 0);
  shapeVAO.LinkVBO(shapeVBO, 1, 4, 6, 2);
  shapeVAO.Unbind();
  shapeVBO.Unbind();
  shapeEBO.Unbind();
  cout << "RectangleShape created" << endl;
}

void RectangleShape::Draw(GLint renderModeLoc) const
{
  glUniform1i(renderModeLoc, BBOP_SHADER_MODE_COLOR);
  shapeVAO.Bind();  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void RectangleShape::updateVBO()
{
  //  coordinate change ########################################
  //  vecteur taille de la fenetre
  Vector2f w(BBOP_WINDOW_SIZE.x/2.0f,BBOP_WINDOW_SIZE.y/2.0f);
  // vecteur de position normalisé
  Vector2f posO(pos.x/w.x-1.0f,pos.y/w.y-1.0f);
  // vecteur position normalizé
  Vector2f pTL(-origin.x/w.x, -origin.y/w.y);
  Vector2f pTR(pTL.x+(size.x/w.x),pTL.y);
  Vector2f pBR(pTR.x,pTL.y+(size.y/w.y));
  Vector2f pBL(pTL.x,pBR.y);
  //application de la rotation
  float cosAngle = cos(rotation);
  float sinAngle = sin(rotation);
  pTL = Vector2f(pTL.x * cosAngle - pTL.y*sinAngle,pTL.x*sinAngle+pTL.y*cosAngle);
  pTR = Vector2f(pTR.x * cosAngle - pTR.y*sinAngle,pTR.x*sinAngle+pTR.y*cosAngle);
  pBR = Vector2f(pBR.x * cosAngle - pBR.y*sinAngle,pBR.x*sinAngle+pBR.y*cosAngle);
  pBL = Vector2f(pBL.x * cosAngle - pBL.y*sinAngle,pBL.x*sinAngle+pBL.y*cosAngle);
  //top right
  vertices[0] = pTR.x+posO.x; vertices[1] = -(pTR.y+posO.y);
  //botton right
  vertices[6] = pBR.x+posO.x; vertices[7] = -(pBR.y+posO.y);
  //bottom left
  vertices[12] = pBL.x+posO.x; vertices[13] = -(pBL.y+posO.y);
  //top left
  vertices[18] = pTL.x+posO.x; vertices[19] = -(pTL.y+posO.y);
  shapeVBO.update(vertices, sizeof(vertices));
  if (autoUpdateCollision){
    shapeCollisionBox.setPosition(pos);
    shapeCollisionBox.setSize(size);
    shapeCollisionBox.setOrigin(origin);
  }
}

void RectangleShape::updateVBORGB()
{
  // color change ########################################
  float r = RGB.x/255.0f;float g = RGB.y/255.0f;float b = RGB.z/255.0f;
  for(int i = 0; i < 24;i+=6){
    vertices[i+2] = r;vertices[i+3] = g; vertices[i+4] = b;
  }
  shapeVBO.update(vertices, sizeof(vertices));
}

void RectangleShape::updateVBOAlpha()
{
  // alpha change ########################################
  for(int i = 0; i < 24;i+=6){
    vertices[i+5] = alpha;
  }
  shapeVBO.update(vertices, sizeof(vertices));
}

ConvexShape::ConvexShape(int nnPoint, Vector2f* nlistPoint)
  : vertices(new GLfloat[nnPoint*6]),
    indices(new GLuint[(nnPoint-1)*3]),
    Shape(vertices, sizeof(GLfloat)*6*nnPoint, indices, sizeof(GLuint)*3*(nnPoint-1)),
    nPoint(nnPoint),
    listPoint(nlistPoint)
{
  buildVAO();
}

void ConvexShape::buildVAO()
{
  for(int i = 0; i < nPoint*6; i++)
    vertices[i] = 0.0f;
  for(int i = 0; i < (nPoint-1)*3; i++)
    indices[i] = 0;
  //construtiopn du VAO fontion de la position du rectangle de sa taille et de la taille de la fenetre
  // init coordinate ########################################
  //  vecteur taille de la fenetre
  Vector2f w(BBOP_WINDOW_SIZE.x/2.0f,BBOP_WINDOW_SIZE.y/2.0f);
  //vecteur de position normalisé
  Vector2f posO(pos.x/w.x-1.0f,pos.y/w.y-1.0f);
  //valeur des couleurs normalisé
  float r = RGB.x/255.0f;float g = RGB.y/255.0f;float b = RGB.z/255.0f;
  //calcule cos et sin pour la rotation
  float cosAngle = cos(rotation);
  float sinAngle = sin(rotation);
  
  for (int i = 0; i < nPoint; i++){
    Vector2f finalPos((listPoint[i].x-origin.x)/w.x, (listPoint[i].y-origin.y)/w.y);
    finalPos = Vector2f(finalPos.x * cosAngle - finalPos.y*sinAngle,finalPos.x*sinAngle+finalPos.y*cosAngle);
    vertices[i*6] = finalPos.x+posO.x; vertices[i*6+1] = -(finalPos.y+posO.y);
    vertices[i*6+2] = r;vertices[i*6+3] = g; vertices[i*6+4] = b;vertices[i*6+5] = alpha;
  }

  for (int i = 0; i < nPoint-1; i++){
    if (i != nPoint-2){
      indices[i*3] = 0;indices[i*3+1] = 1+i; indices[i*3+2] = 2+i;
    }else {
      indices[i*3] = 0;indices[i*3+1] = 1+i; indices[i*3+2] = 1;
    }
  }
  shapeVAO.Bind();
  shapeVBO.update(vertices, sizeof(GLfloat)*6*nPoint);
  shapeEBO.update(indices, sizeof(GLuint)*3*(nPoint-1));
  shapeVAO.LinkVBO(shapeVBO, 0, 2, 6, 0);
  shapeVAO.LinkVBO(shapeVBO, 1, 4, 6, 2);
  shapeVAO.Unbind();
  shapeVBO.Unbind();
  shapeEBO.Unbind();
  cout << "ConvexShape created" << endl;
}

void ConvexShape::updateVBO()
{
  //  vecteur taille de la fenetre
  Vector2f w(BBOP_WINDOW_SIZE.x/2.0f,BBOP_WINDOW_SIZE.y/2.0f);
  //vecteur de position normalisé
  Vector2f posO(pos.x/w.x-1.0f,pos.y/w.y-1.0f);
  //calcule cos et sin pour la rotation
  float cosAngle = cos(rotation);
  float sinAngle = sin(rotation);

  for (int i = 0; i < nPoint; i++){
    Vector2f finalPos((listPoint[i].x-origin.x)/w.x, (listPoint[i].y-origin.y)/w.y);
    finalPos = Vector2f(finalPos.x * cosAngle - finalPos.y*sinAngle,finalPos.x*sinAngle+finalPos.y*cosAngle);
    vertices[i*6] = finalPos.x+posO.x; vertices[i*6+1] = -(finalPos.y+posO.y);
  }

  shapeVBO.update(vertices, sizeof(GLfloat)*6*nPoint);
}

void ConvexShape::updateVBORGB()
{
  //valeur des couleurs normalisé
  float r = RGB.x/255.0f;float g = RGB.y/255.0f;float b = RGB.z/255.0f;

  for (int i = 0; i < nPoint; i++){
    vertices[i*6+2] = r;vertices[i*6+3] = g; vertices[i*6+4] = b;
  }

  shapeVBO.update(vertices, sizeof(GLfloat)*6*nPoint);
}

void ConvexShape::updateVBOAlpha()
{
  for (int i = 0; i < nPoint; i++){
    vertices[i*6+5] = alpha;
  }

  shapeVBO.update(vertices, sizeof(GLfloat)*6*nPoint);
}


void ConvexShape::Draw(GLint renderModeLoc) const
{
  glUniform1i(renderModeLoc, BBOP_SHADER_MODE_COLOR);
  shapeVAO.Bind();  
  glDrawElements(GL_TRIANGLES, 3*(nPoint-1), GL_UNSIGNED_INT, 0);
}

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
    rotation(0.0f)
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

CollisionBox* Shape::getCollisionBox()
{
  return &shapeCollisionBox;
}

bool Shape::isInCollision(CollisionBox* box)
{
  return shapeCollisionBox.check(box);
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
  //top right
  vertices[0] = ((pos.x-origin.x+size.x)/(BIBIBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[1] = ((-pos.y+origin.y)/(BIBIBOP_WINDOW_SIZE.y/2.0f))+1.0f;
  vertices[3] = RGB.x/255.0f; vertices[4] = RGB.x/255.0f; vertices[5] = RGB.x/255.0f;
  //botton right
  vertices[6] = ((pos.x-origin.x+size.x)/(BIBIBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[7] = ((-pos.y+origin.y-size.y)/(BIBIBOP_WINDOW_SIZE.y/2.0f))+1.0f;
  vertices[9] = RGB.x/255.0f; vertices[10] = RGB.x/255.0f; vertices[11] = RGB.x/255.0f;
  //bottom left
  vertices[12] = ((pos.x-origin.x)/(BIBIBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[13] = ((-pos.y+origin.y-size.y)/(BIBIBOP_WINDOW_SIZE.y/2.0f))+1.0f;
  vertices[15] = RGB.x/255.0f; vertices[16] = RGB.x/255.0f; vertices[17] = RGB.x/255.0f;
  //top left
  vertices[18] = ((pos.x-origin.x)/(BIBIBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[19] = ((-pos.y+origin.y)/(BIBIBOP_WINDOW_SIZE.y/2.0f))+1.0f;
  vertices[21] = RGB.x/255.0f; vertices[22] = RGB.x/255.0f; vertices[23] = RGB.x/255.0f;
  indices[0] = 0;indices[1] = 1;indices[2] = 3;indices[3] = 1;indices[4] = 2;indices[5] = 3;
  shapeVAO.Bind();  
  shapeVBO.update(vertices, sizeof(vertices));
  shapeEBO.update(indices, sizeof(indices));
  shapeVAO.LinkVBO(shapeVBO, 0, 3, 6, 0);
  shapeVAO.LinkVBO(shapeVBO, 1, 3, 6, 3);
  shapeVAO.Unbind();
  shapeVBO.Unbind();
  shapeEBO.Unbind();
  cout << "RectangleShape created" << endl;
}

void RectangleShape::Draw(GLint renderModeLoc) const
{
  glUniform1i(renderModeLoc, BIBIBOP_SHADER_MODE_COLOR);
  shapeVAO.Bind();  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void RectangleShape::updateVBO()
{
  //  coordinate change ########################################
  //  vecteur taille de la fenetre
  Vector2f w(BIBIBOP_WINDOW_SIZE.x/2.0f,BIBIBOP_WINDOW_SIZE.y/2.0f);
  // vecteur position normalizé
  Vector2f p(((pos.x-origin.x)/w.x)-1.0f, ((-pos.y+origin.y)/w.y)+1.0f);
  // vecteur position normalizé avec la taille en plus
  Vector2f ps(p.x+(size.x/w.x),p.y-(size.y/w.y));
  //top right
  vertices[0] = ps.x; vertices[1] = p.y;
  //botton right
  vertices[6] = ps.x; vertices[7] = ps.y;
  //bottom left
  vertices[12] = p.x; vertices[13] = ps.y;
  //top left
  vertices[18] = p.x; vertices[19] = p.y;
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
    vertices[i+3] = r;vertices[i+4] = g; vertices[i+5] = b;
  }
  shapeVBO.update(vertices, sizeof(vertices));
}

#include "../include/shapeClass.h"

Shape::Shape(GLfloat* vertices, GLsizeiptr verticesSize, GLuint* indices, GLsizeiptr indicesSize)
  : shapeVBO(vertices, verticesSize, GL_DYNAMIC_DRAW),
    shapeEBO(indices, indicesSize),
    pos(0.0f, 0.0f),
    size(0.0f, 0.0f),
    origin(0.0f, 0.0f) 
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

RectangleShape::RectangleShape()
  : Shape(vertices, sizeof(vertices), indices, sizeof(indices))
{
  size.x = 500.0f, size.y = 500.0f;
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
  vertices[3] = 1.0f; vertices[4] = 1.0f; vertices[5] = 1.0f;
  //botton right
  vertices[6] = ((pos.x-origin.x+size.x)/(BIBIBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[7] = ((-pos.y+origin.y-size.y)/(BIBIBOP_WINDOW_SIZE.y/2.0f))+1.0f;
  vertices[9] = 1.0f; vertices[10] = 1.0f; vertices[11] = 1.0f;
  //bottom left
  vertices[12] = ((pos.x-origin.x)/(BIBIBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[13] = ((-pos.y+origin.y-size.y)/(BIBIBOP_WINDOW_SIZE.y/2.0f))+1.0f;
  vertices[15] = 1.0f; vertices[16] = 1.0f; vertices[17] = 1.0f;
  //top left
  vertices[18] = ((pos.x-origin.x)/(BIBIBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[19] = ((-pos.y+origin.y)/(BIBIBOP_WINDOW_SIZE.y/2.0f))+1.0f;
  vertices[21] = 1.0f; vertices[22] = 1.0f; vertices[23] = 1.0f;
  indices[0] = 0;indices[1] = 1;indices[2] = 3;indices[3] = 1;indices[4] = 2;indices[5] = 3;
  shapeVAO.Bind();  
  shapeVBO.update(vertices, sizeof(vertices));
  shapeEBO.update(indices, sizeof(indices));
  shapeVAO.LinkVBO(shapeVBO, 0, 3, 6, 0);
  shapeVAO.LinkVBO(shapeVBO, 1, 3, 6, 3);
  shapeVAO.Unbind();
  shapeVBO.Unbind();
  shapeEBO.Unbind();
}

void RectangleShape::Draw(GLint renderModeLoc) const
{
  glUniform1i(renderModeLoc, BIBIBOP_SHADER_MODE_COLOR);
  shapeVAO.Bind();  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void RectangleShape::updateVBO()
{

}

#ifndef SHAPE_CLASS_H
#define SHAPE_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "bbopMathClass.h"
#include "bbopGlobal.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Shape : public BbopDrawable
{
public:
  Shape(GLfloat* vertices, GLsizeiptr verticesSize, GLuint* indices, GLsizeiptr indicesSize);
  
  virtual void buildVAO() = 0;
  virtual void updateVBO() = 0;
  Vector2f getSize();
  void setSize(Vector2f nSize);
  Vector2f getPosition();
  void setPosition(Vector2f nPos);
  Vector2f getOrigin();
  void setOrigin(Vector2f nOrigin);
protected:
  VAO shapeVAO;
  VBO shapeVBO;
  EBO shapeEBO;
  Vector2f pos;
  Vector2f size;
  Vector2f origin;
};

class RectangleShape : public Shape
{
public:
  RectangleShape();
  
  void buildVAO() override;
  void updateVBO() override;
  void Draw(GLint renderModeLoc) const override;
private:
  GLfloat vertices[24];
  GLuint indices[6];
};

class CircleShape : public Shape
{
public:
  CircleShape();

  void buildVAO() override;
  void updateVBO() override;
  void Draw(GLint renderModeLoc) const override;
};

#endif // ! SHAPE_CLASS_H

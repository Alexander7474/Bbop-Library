#ifndef SHAPE_CLASS_H
#define SHAPE_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <initializer_list>

#include "bbopMathClass.h"
#include "bbopGlobal.h"
#include "collisonBoxClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Shape : public BbopDrawable
{
public:
  Shape(GLfloat* vertices, GLsizeiptr verticesSize, GLuint* indices, GLsizeiptr indicesSize);
  Shape();

  void initShape(GLfloat* vertices, GLsizeiptr verticesSize, GLuint* indices, GLsizeiptr indicesSize);
  virtual void buildVAO() = 0;
  virtual void updateVBO() = 0;
  virtual void updateVBORGB() = 0;
  virtual void updateVBOAlpha() = 0;
  Vector2f getSize();
  void setSize(Vector2f nSize);
  Vector2f getPosition();
  void setPosition(Vector2f nPos);
  Vector2f getOrigin();
  void setOrigin(Vector2f nOrigin);
  Vector3i getColor();
  void setColor(Vector3i nRGB);
  float getAlpha();
  void setAlpha(float nAlpha);
  float getRotation();
  void setRotation(float nRotation);
  CollisionBox* getCollisionBox();
  void setAutoUpdateCollision(bool etat); 
  void move(Vector2f vecM);
protected:
  VAO shapeVAO;
  VBO shapeVBO;
  EBO shapeEBO;
  Vector2f pos;
  Vector2f size;
  Vector2f origin;
  Vector3i RGB;
  bool autoUpdateCollision;
  float rotation;
  CollisionBox shapeCollisionBox;
  float alpha;
};

class RectangleShape : public Shape
{
public:
  RectangleShape();
  RectangleShape(Vector2f nSize, Vector2f nPos);
  RectangleShape(Vector2f nSize, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin);
  RectangleShape(Vector2f nSize, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin, float nRotation, float nAlpha);
  
  void buildVAO() override;
  void updateVBO() override;
  void updateVBORGB() override;
  void updateVBOAlpha() override;
  void Draw(GLint renderModeLoc) const override;
private:
  GLfloat vertices[24];
  GLuint indices[6];
};

class ConvexShape : public Shape
{
public:
  ConvexShape();
  ConvexShape(int nnPoint, Vector2f* nlistPoint);
  ConvexShape(int nnPoint, Vector2f* nlistPoint, Vector2f nSize, Vector2f nPos);
  ConvexShape(int nnPoint, Vector2f* nlistPoint, Vector2f nSize, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin);
  ConvexShape(int nnPoint, Vector2f* nlistPoint, Vector2f nSize, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin, float nRotation, float nAlpha);

  ConvexShape(const ConvexShape& other);
  ~ConvexShape();

  ConvexShape& operator=(const ConvexShape& other);

  void initConvex(int nnPoint, Vector2f* nlistPoint);
  void buildVAO() override;
  void updateVBO() override;
  void updateVBORGB() override;
  void updateVBOAlpha() override;
  void Draw(GLint renderModeLoc) const override;
private:
  GLfloat* vertices;
  GLuint* indices;
  int nPoint;
  Vector2f* listPoint;
};

class CircleShape : public ConvexShape
{
public:
  CircleShape(int nnPoint, float nRadius);
  CircleShape(int nnPoint, float nRadius, Vector2f nSize, Vector2f nPos);
  CircleShape(int nnPoint, float nRadius, Vector2f nSize, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin);
  CircleShape(int nnPoint, float nRadius, Vector2f nSize, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin, float nRotation, float nAlpha);

  void buildConvex();
  float getRadius();
  void setRadius(float nRadius);
  int getNPointCircle();
  void setNPointCircle(int nnPoint);
private:
  float radius;
  int nPointCircle;
};

#endif // ! SHAPE_CLASS_H

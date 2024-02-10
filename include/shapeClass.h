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
  Shape();
  
  void buildVAO();
  void updateVBO();
  void Draw() const override;
private:
  int windowX, windowY;
  VAO shapeVAO;
  VBO shapeVBO;
  EBO shapeEBO;
  GLfloat vertices[32];
  GLuint indices[6];
  GLFWwindow* window;
  Vector2f pos;
  Vector2f size;
  Vector2f origin;
};

#endif // ! SHAPE_CLASS_H

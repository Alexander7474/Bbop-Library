#ifndef SPRITE_CLASS_H
#define SPRITE_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "textureClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

using namespace std;

class Sprite
{
public:
  Sprite(const char* textureFileName, GLFWwindow* win);

  void Draw();
  void setPosition(float nx, float ny);
  float getPositionX();
  float getPositionY();
  void setSize(float nWidth, float nHeight);
  float getWidth();
  float getHeight();
  void setOrigin(float nOriginX, float nOriginY);
  float getOriginX();
  float getOriginY();
  void setTexture(Texture nTexture);
  void buildVAO();
  void updateVBO();
private:
  int windowX, windowY;
  Texture spriteTexture;
  VAO spriteVAO;
  VBO spriteVBO;
  EBO spriteEBO;
  GLfloat spriteVertices[32];
  GLuint spriteIndices[6];
  float x; 
  float y;
  float width;
  float height;
  float originX;
  float originY;
  GLFWwindow* spriteWindow;
 };
#endif // !SPRITE_CLASS_H

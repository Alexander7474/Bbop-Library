#ifndef SPRITE_CLASS_H
#define SPRITE_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

using namespace std;

class Sprite
{
public:
  Sprite(const char* textureFileName, GLFWwindow* win);

  void Draw();
private:
  Shader spriteShader;
  VAO spriteVAO;
  GLuint spriteTexture;
  GLfloat spriteVertices[32];
  float x; 
  float y;
  float sizeX;
  float sizeY;
  GLFWwindow* spriteWindow;
 };
#endif // !SPRITE_CLASS_H

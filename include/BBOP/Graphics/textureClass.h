#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "bbopMathClass.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Texture 
{
public:
  Texture(const char* textureFileName);
  
  void Bind() const;
  void Unbind() const;
  void Delete();
  int getWidth();
  int getHeight();
private:
  GLuint ID;
  int width, height, nrChannels;
};

#endif // !TEXTURE_CLASS_H

#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

#include "bbopGlobal.h"

class Shader
{
public:
	// ID de reference shader program
	GLuint ID;
	// BUILDER creation du shader program
	Shader(const char* vertexFile, const char* fragmentFile);

  GLint getUniformLoc(const GLchar* varName) const;
  GLuint getID() const;
  void Activate() const;
	void Delete();
};
#endif

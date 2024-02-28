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

  GLint getUniformLoc(const GLchar* varName);
  GLuint getID();
  void setInt(const GLchar* varName, GLint value);
	void setFloat(const GLchar* varName, GLfloat value);
  void setBool(const GLchar* varName, GLboolean value);
  void Activate() const;
	void Delete();
};
#endif

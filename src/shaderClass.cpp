#include "../include/shaderClass.h"

using namespace std;

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	string vertexCode = getFileData(vertexFile);
	string fragmentCode = getFileData(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();
 
	// creation du vertexShader et recup de la reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// recup u code source du shader
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile
	glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

	// meme chose avec le fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

	// Creation shader programme
	ID = glCreateProgram();
	// Ajout du vertex shader et du fragment shader dans le prog
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// link de tous les shaders
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLuint Shader::getUniformLoc(const GLchar* varName)
{
  return glGetUniformLocation(ID, varName);
}

void Shader::setInt(const GLchar* varName, GLint value){
  glUniform1i(glGetUniformLocation(ID, varName), value);
}

void Shader::setFloat(const GLchar* varName, GLfloat value){
  glUniform1f(glGetUniformLocation(ID, varName), value);
}

void Shader::setBool(const GLchar* varName, GLboolean value){
  glUniform1i(glGetUniformLocation(ID, varName), (int)value);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

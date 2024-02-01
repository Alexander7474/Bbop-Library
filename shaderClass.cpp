#include "include/shaderClass.h"

using namespace std;

// Lecture du fichier text et sortie en string
string get_file_contents(const char* filename)
{
	ifstream in(filename, ios::binary);
	if (in)
	{
		string contents;
		in.seekg(0, ios::end);
		contents.resize(in.tellg());
		in.seekg(0, ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	string vertexCode = get_file_contents(vertexFile);
	string fragmentCode = get_file_contents(fragmentFile);

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

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

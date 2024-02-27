#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include"VBO.h"

class VAO
{
public:
	// ID reference for the Vertex Array Object
	GLuint ID;
	// Constructor that generates a VAO ID
	VAO();

	// Links a VBO to the VAO using a certain layout
	void LinkVBO(VBO& VBO, GLuint layout, GLuint vecN, GLuint strideN, GLuint jump);
	// Binds the VAO
	void Bind() const;
	// Unbinds the VAO
	void Unbind() const;
	// Deletes the VAO
	void Delete();
};
#endif

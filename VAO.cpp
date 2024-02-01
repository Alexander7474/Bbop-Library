#include "include/VAO.h"

// Constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO to the VAO using a certain layout
void VAO::LinkVBO(VBO& VBO, GLuint layout, GLuint vecN, GLuint strideN, GLuint jump)
{
	VBO.Bind();
	glVertexAttribPointer(layout, vecN, GL_FLOAT, GL_FALSE, strideN* sizeof(float), (void*)(jump * sizeof(float)));
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Binds the VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}

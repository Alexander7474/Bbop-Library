#include "../../../include/BBOP/Graphics/VBO.h"

// Constructor that generates a Vertex Buffer Object and links it to vertices
VBO::VBO(GLfloat* vertices, GLsizeiptr size, GLenum typeVBO)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, typeVBO);
}

// Binds the VBO
void VBO::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}

void VBO::update(GLfloat* vertices, GLsizeiptr size){
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
}


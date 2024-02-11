#include "../../../include/BBOP/Graphics/EBO.h"

// Constructor that generates a Elements Buffer Object and links it to indices
EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

// Binds the EBO
void EBO::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds the EBO
void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}

void EBO::update(GLuint* indices, GLsizeiptr size)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, indices);
}


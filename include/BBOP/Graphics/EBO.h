#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);

	// Binds the EBO
	void Bind() const;
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();
  // update the EBO
  void update(GLuint* indices, GLsizeiptr size);
};

#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "include/shaderClass.h"
#include "include/VAO.h"
#include "include/VBO.h"
#include "include/EBO.h"


using namespace std;

int main() {
    //Initialisation Début ############################################################################
    // Initialisation de GLFW
    if (!glfwInit()) {
        cerr << "Échec de l'initialisation de GLFW" << endl;
        return -1;
    }

    // Configuration de GLFW pour utiliser le profil OpenGL Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Création d'une fenêtre GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "Bibibop engine", nullptr, nullptr);
    if (!window) {
        cerr << "Échec de la création de la fenêtre GLFW" << endl;
        glfwTerminate();
        return -1;
    }

    // Définition de la fenêtre comme le contexte OpenGL courant
    glfwMakeContextCurrent(window);

    // Initialisation de GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cerr << "Échec de l'initialisation de GLEW" << endl;
        glfwTerminate();
        return -1;
    }
    // Initialisation Fin ##############################################################################

    // Compilation et liaison des shaders ##############################################################
    Shader shaderProgram("shaders/default.vert", "shaders/default.frag");
    Shader shaderProgram2("shaders/default.vert", "shaders/defaultCustomColor.frag");
    //Compilation des shaders fin ######################################################################

    // Définition des vertices du triangle
    GLfloat vertices[] = {
      0.5f,  0.5f, 0.0f,  // top right
      0.5f, -0.5f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f,  // bottom left
      -0.5f,  0.5f, 0.0f   // top lef
    };

    GLfloat vertices2[] = {
      0.8f,  0.8f, 0.0f,   
      0.7f,  0.7f, 0.0f, 
      0.9f,  0.7f, 0.0f, 
    };

    GLuint indices[] =
    {
      0, 1, 3,   // premier triangle
      1, 2, 3    // second triangle
    };

    GLuint indices2[] =
    {
      0, 1, 2   
    };
    
  // Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
 
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	 
  VAO VAO2;
	VAO2.Bind();

  VBO VBO2(vertices2, sizeof(vertices2));

  EBO EBO2(indices2, sizeof(indices2));

  VAO2.LinkVBO(VBO2, 0);
  VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();
  
  // Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f)+0.5f;
    GLuint vertexColorLocation = shaderProgram2.getUniformLoc("outColor");
    shaderProgram2.Activate();
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		VAO2.Bind();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    // Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}

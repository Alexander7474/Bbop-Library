#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
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
    Shader shaderProgram("default.vert", "default.frag");
    //Compilation des shaders fin ######################################################################

    // Définition des vertices du triangle
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,
        -0.25f, 0.0f, 0.0f,
        0.25f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f
    };

    GLuint indices[] =
    {
        0, 3, 5,
        3, 2, 4,
        4, 5, 1
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

    // Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
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

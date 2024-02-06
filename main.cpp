#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
//#include <cmath>
//#include <stdio.h>
//#include <stdlib.h>

#include "include/spriteClass.h"

using namespace std;

int WINDOW_X = 960;
int WINDOW_Y = 1080;

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
  GLFWwindow* window = glfwCreateWindow(WINDOW_X, WINDOW_Y, "Bibibop engine", nullptr, nullptr);
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
  // Désactiver la synchronisation verticale (V-Sync)
  glfwSwapInterval(0);
  //General info
  cout << "Bibibop Engine Version 0.0.1" << endl << "Author: Alexander74" << endl << "Contact: alexandre.lanternier@outlook.fr" << endl << "License: GNU 3.0" << endl; 
  //GPU info
  const GLubyte* vendor = glGetString(GL_VENDOR);
  const GLubyte* renderer = glGetString(GL_RENDERER);
  cout << "OpenGL Vendor: " << vendor << endl;
  cout << "OpenGL Renderer: " << renderer << endl;
  cout << "Window size: " << WINDOW_X << "x" << WINDOW_Y << endl;
  // Initialisation Fin ##############################################################################
  Sprite testspr("imgTesting/mario.png", window);
  testspr.setPosition(0.0f, 0.0f);
  testspr.setSize(200.0f,220.0f);
  //FPS counter
  int nbFrames = 0;
  double lastTime = glfwGetTime();
  //FPS end init #######
  // Main while loop
	while (!glfwWindowShouldClose(window))
	{
    // FPS calc ################################################
    double currentTime = glfwGetTime();
    double delta = currentTime - lastTime;
    nbFrames++;
    if ( delta >= 1.0 ){ // If last cout was more than 1 sec ago
      double fps = double(nbFrames) / delta;

      stringstream ss;
      ss << "BibibopEngine" << " [" << fps << " FPS]";

      glfwSetWindowTitle(window, ss.str().c_str());
      nbFrames = 0;
      lastTime = currentTime;
    }
    //FPS calc end #############################################
		// Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
    //cout << testspr.getPositionX() << ";" << testspr.getPositionY() << endl;
    //testspr.setPosition(testspr.getPositionX()+0.5f, testspr.getPositionY()+0.5f);
    testspr.Draw();
    //Check d'erreur
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
      std::cerr << "OpenGL error: " << error << std::endl;
    }
    // Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}

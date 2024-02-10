#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
//#include <cmath>
//#include <stdio.h>
//#include <stdlib.h>

//#include "include/bbopGlobal.h"
#include "include/bbopGlobal.h"
#include "include/spriteClass.h"
#include "include/textureClass.h"
#include "include/sceneClass.h"
#include "include/bbopMathClass.h"

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
  GLFWwindow* window = glfwCreateWindow(BIBIBOP_WINDOW_SIZE.x, BIBIBOP_WINDOW_SIZE.y, "Bibibop engine", nullptr, nullptr);
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
  //glfwSwapInterval(0);
  //General info
  cout << "Bibibop Engine Version 0.0.1" << endl << "Author: Alexander74" << endl << "Contact: alexandre.lanternier@outlook.fr" << endl << "License: GPL-3.0" << endl; 
  //GPU info
  const GLubyte* vendor = glGetString(GL_VENDOR);
  const GLubyte* renderer = glGetString(GL_RENDERER);
  cout << "OpenGL Vendor: " << vendor << endl;
  cout << "OpenGL Renderer: " << renderer << endl;
  cout << "Window size: " << BIBIBOP_WINDOW_SIZE.x << "x" << BIBIBOP_WINDOW_SIZE.y << endl;
  // Initialisation Fin ##############################################################################
  //creation du sprite
  Sprite testspr("imgTesting/mario.png", window);
  testspr.setSize(Vector2f(200.0f, 220.0f));
  double speed = 10.0f;
  //creation de la sceneClass
  Scene defaultScene;
  //FPS counter
  int nbFrames = 0;
  //double frameTarget = 1.0/60.0;
  double lastTime = glfwGetTime();
  double fps;
  double currentTime;
  double delta;
  double totalFps = 0.0;
  //FPS end init #######
  // Main while loop
	while (!glfwWindowShouldClose(window))
	{
    // FPS calc ################################################
    currentTime = glfwGetTime();
    delta = currentTime - lastTime;
    nbFrames++;
    totalFps++;
    if ( delta >= 1.0 ){ // If last cout was more than 1 sec ago
      fps = double(nbFrames) / delta;
      stringstream ss;
      ss << "BibibopEngine" << " [" << fps << " FPS]";

      glfwSetWindowTitle(window, ss.str().c_str());
      nbFrames = 0;
      lastTime = currentTime;
    }
    //FPS calc end #############################################
		
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
      testspr.move(Vector2f(speed,0.0f)); 
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
      testspr.move(Vector2f(-speed,0.0f)); 
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
      testspr.move(Vector2f(0.0f,-speed)); 
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
      testspr.move(Vector2f(0.0f,speed)); 
    }
    if(glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS){
      testspr.setSize(Vector2f(testspr.getSize().x+speed, testspr.getSize().y+speed));
    }
    if(glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS){
      testspr.setSize(Vector2f(testspr.getSize().x-speed, testspr.getSize().y-speed));
    }
    if(glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS){
      testspr.setOrigin(Vector2f(testspr.getOrigin().x+1.0f, testspr.getOrigin().y+1.0f));
    }
    if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS){
      testspr.setOrigin(Vector2f(testspr.getOrigin().x-1.0f, testspr.getOrigin().y-1.0f));
    }
    if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS){
      testspr.setTexture(Texture("imgTesting/ario.png"));
    }
    // Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
    //testspr.setPosition(testspr.getPositionX()+0.5f, testspr.getPositionY()+0.5f);
    defaultScene.Use();
    defaultScene.Draw(testspr); 
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
  testspr.Delete();
  defaultScene.Delete();
  cout << "Session terminated, avg fps: " << totalFps/glfwGetTime() << endl;
	glfwTerminate();
	return 0;
}

////////////////////////////////////////////////////////////////////
//CECI N'EST QU'UN EXEMPLE POUR TESTER SI BBOP EST BIEN INSTALLER
////////////////////////////////////////////////////////////////////
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "include/BBOP/Graphics.h"

using namespace std;

int main() {
  
  GLFWwindow * window;
  bbopInit(956,1044,"test",window);
  
  //Creation de la scene pour afficher nos formes
  cout << "creation de la scene" << endl;
  Scene defaultScene(1.0f,Vector3i(255,255,255));
  //creation d'un rectangle a afficher, par default blanc en haut a gauche de l'image
  
  Vector2f list[8] = {Vector2f(0.0f,0.0f), Vector2f(124.0f,56.0f), Vector2f(32.0f,125.0f), Vector2f(52.0f,250.0f),Vector2f(0.0f,0.0f), Vector2f(124.0f,56.0f), Vector2f(32.0f,125.0f), Vector2f(52.0f,250.0f)};
  ConvexShape defaultConvex(8,list);

  // Main while loop
	while (!glfwWindowShouldClose(window))
	{
    bbopCleanWindow(window, Vector3i(0,0,0),1.0);

    //////////////////////////////////////////////////////////////
    ///code zone
    //////////////////////////////////////////////////////////////
    
    defaultScene.Use();
    defaultScene.Draw(defaultConvex);

    //////////////////////////////////////////////////////////////
    
    bbopErrorCheck();

    // Swap the back buffer with the front buffer
	  glfwSwapBuffers(window);
	  glfwPollEvents();
	}
	// Delete window before ending the program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

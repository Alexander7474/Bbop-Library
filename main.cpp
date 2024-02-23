////////////////////////////////////////////////////////////////////
//CECI N'EST QU'UN EXEMPLE POUR TESTER SI BBOP EST BIEN INSTALLER
////////////////////////////////////////////////////////////////////
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "include/BBOP/Graphics.h"

int main() {
  
  GLFWwindow * window;
  bbopInit(956,1044,"test",window);
  
  //Creation de la scene pour afficher nos formes
  Scene defaultScene;
  //creation d'un rectangle a afficher, par default blanc en haut a gauche de l'image
  RectangleShape defaultRect;

  // Main while loop
	while (!glfwWindowShouldClose(window))
	{
    bbopCleanWindow();

    //////////////////////////////////////////////////////////////
    ///code zone
    //////////////////////////////////////////////////////////////
   
    //utilisation de la scene par default
    defaultScene.Use();
    //affichage du rectangle 
    defaultScene.Draw(defaultRect);

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

////////////////////////////////////////////////////////////////////
//CECI N'EST QU'UN EXEMPLE POUR TESTER SI BBOP EST BIEN INSTALLER
////////////////////////////////////////////////////////////////////
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "include/BBOP/Graphics.h"
#include "include/BBOP/Graphics/spriteClass.h"

int main() {
  
  GLFWwindow * window;
  bbopInit(956,1044,"test",window);
  
  //Creation de la scene pour afficher nos formes
  Scene defaultScene;
  //creation d'un rectangle a afficher, par default blanc en haut a gauche de l'image
  RectangleShape defaultRect;
  defaultRect.setSize(Vector2f(100.0f,100.0f));
  defaultRect.setOrigin(Vector2f(50.0f,50.0f));
  defaultRect.setColor(Vector3i(15,182,245));
  defaultRect.setPosition(Vector2f(BBOP_WINDOW_SIZE.x/2.0f,BBOP_WINDOW_SIZE.y/2.0f));

  Sprite defaultSprite("imgTesting/mario.png");

  // Main while loop
	while (!glfwWindowShouldClose(window))
	{
    bbopCleanWindow(Vector3i(0,0,0),1.0);

    //////////////////////////////////////////////////////////////
    ///code zone
    //////////////////////////////////////////////////////////////

    //utilisation de la scene par default
    defaultScene.Use();
    //affichage du rectangle 
    defaultRect.setRotation(defaultRect.getRotation()+0.1);
    //defaultScene.Draw(defaultRect);
    defaultScene.Draw(defaultSprite);

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

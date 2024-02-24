////////////////////////////////////////////////////////////////////
//CECI N'EST QU'UN EXEMPLE POUR TESTER SI BBOP EST BIEN INSTALLER
////////////////////////////////////////////////////////////////////
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "include/BBOP/Graphics.h"
#include "include/BBOP/Graphics/shapeClass.h"

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
  defaultRect.setAlpha(0.5f);

  Sprite defaultSprite("imgTesting/mario.png");
  defaultSprite.setAlpha(0.5f);
  defaultSprite.setSize(Vector2f(100.0f,100.0f));
  defaultSprite.setRGBFilterState(true);
 
  Vector2f list[6] = {Vector2f(100.0f,100.0f),Vector2f(170.0f,10.0f),Vector2f(189.0f,75.0f),Vector2f(189.0f,199.0f),Vector2f(32.0f,112.0f),Vector2f(15.0f,17.0f)};
  ConvexShape defaultConvex(6,list);
  defaultConvex.setPosition(Vector2f(750.0f,50.0f));
  defaultConvex.setColor(Vector3i(100,0,255));

  // Main while loop
	while (!glfwWindowShouldClose(window))
	{
    bbopCleanWindow(Vector3i(0,0,0),1.0);

    //////////////////////////////////////////////////////////////
    ///code zone
    //////////////////////////////////////////////////////////////
    
    //test des collision entre sprite et rectangle par default
    if(defaultSprite.getCollisionBox()->check(defaultRect.getCollisionBox()))
      cout << "hit" << glfwGetTime() << endl;
    //utilisation de la scene par default
    defaultScene.Use();
    //affichage du rectangle  avec sa rotation
    defaultRect.setRotation(defaultRect.getRotation()+0.1);
    defaultScene.Draw(defaultRect);
    //affichage du sprite mario, texture par default si non trouvé
    defaultScene.Draw(defaultSprite);
    defaultConvex.setRotation(defaultConvex.getRotation()+0.01);
    //affichage de la forme convex
    defaultScene.Draw(defaultConvex);

    //gestiond des mouvement de mario
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
      defaultSprite.move(Vector2f(0.0f,-5.0f));
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
      defaultSprite.move(Vector2f(0.0f,5.0f));
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
      defaultSprite.move(Vector2f(5.0f,0.0f));   
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
      defaultSprite.move(Vector2f(-5.0f,0.0f));
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

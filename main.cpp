////////////////////////////////////////////////////////////////////
//CECI N'EST QU'UN EXEMPLE POUR TESTER SI BBOP EST BIEN INSTALLER
////////////////////////////////////////////////////////////////////
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "include/BBOP/Graphics.h"
#include "include/BBOP/Graphics/bbopGlobal.h"

using namespace std;

int main() {
  
  GLFWwindow * window;
  bbopInit(956,1044,"test",window);
  
  //Creation de la scene pour afficher nos formes
  cout << "creation de la scene" << endl;
  Scene defaultScene(0.5f,Vector3i(255,255,255));
  //creation d'un rectangle a afficher, par default blanc en haut a gauche de l'image
  cout << "creation du rectangle" << endl;
  RectangleShape defaultRect(Vector2f(100.0f,100.0f),Vector2f(BBOP_WINDOW_SIZE.x/2.0f,BBOP_WINDOW_SIZE.y/2.0f),Vector3i(15,182,245),Vector2f(-100.0f,-100.0f));

  cout << "creation du sprite" << endl;
  Sprite defaultSprite(Texture("imgTesting/mario.png"), Vector2f(150.0f,150.0f));
  defaultSprite.setSize(Vector2f(100.0f,100.0f));
  defaultSprite.setOrigin(Vector2f(50.0f,50.0f));

  cout << "creation de la forme convex" << endl;
  Vector2f list[6] = {Vector2f(100.0f,100.0f),Vector2f(170.0f,10.0f),Vector2f(189.0f,75.0f),Vector2f(189.0f,199.0f),Vector2f(32.0f,112.0f),Vector2f(0.0f,0.0f)};
  ConvexShape defaultConvex(6,list,Vector2f(1.0f,1.0f),Vector2f(650.0f,250.0f));
  defaultConvex.setColor(Vector3i(100,0,255));

  CircleShape circleDefault(99, 50.0f);

  Camera cam(defaultSprite.getPosition(),1.0f);


  // Main while loop
	while (!glfwWindowShouldClose(window))
	{
    bbopCleanWindow(window, Vector3i(0,0,0),1.0);

    //////////////////////////////////////////////////////////////
    ///code zone
    //////////////////////////////////////////////////////////////
    
    cam.setPosition(defaultSprite.getPosition());
    defaultScene.Use();
    defaultScene.useCamera(&cam);
    //affichage du rectangle  avec sa rotation
    defaultRect.setRotation(defaultRect.getRotation()+0.1);
    defaultScene.Draw(defaultRect);
    //affichage du sprite mario, texture par default si non trouvé
    defaultScene.Draw(defaultSprite);
    //affichage de la forme convex
    defaultConvex.setRotation(defaultConvex.getRotation()+0.01);
    defaultScene.Draw(defaultConvex);

    defaultScene.Draw(circleDefault);


    //gestiond des mouvement de mario
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
      defaultSprite.move(Vector2f(0.0f,-5.0f));
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
      defaultSprite.move(Vector2f(0.0f,5.0f));
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
      defaultSprite.move(Vector2f(5.0f,0.0f));   
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
      defaultSprite.move(Vector2f(-5.0f,0.0f));

    if(defaultSprite.getCollisionBox()->checkWithRotation(defaultRect.getCollisionBox()))
      cout << glfwGetTime() << endl;

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

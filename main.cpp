////////////////////////////////////////////////////////////////////
//CECI N'EST QU'UN EXEMPLE POUR TESTER SI BBOP EST BIEN INSTALLER
////////////////////////////////////////////////////////////////////
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <string>

#include "include/BBOP/Graphics.h"

using namespace std;

int main() {
  
  GLFWwindow * window;
  bbopInit(956,1044,"test",window);
  
  //Creation de la scene pour afficher nos formes
  Scene defaultScene(0.0f,Vector3i(255,255,255));
  //creation d'un rectangle a afficher, par default blanc en haut a gauche de l'image

  Sprite defaultSprite(Texture("imgTesting/anim/00001.png"), Vector2f(0.0f,0.0f), Vector3i(255,255,255), Vector2f(50.0f,50.0f));
  defaultSprite.setSize(Vector2f(100.0f,100.0f));
  std::vector<Texture> animList;
  int animState = 0;
  for(int i = 0; i < 19; i++){
    std::string file;
    if(i < 10-1)
      file = "imgTesting/anim/0000"+std::to_string(i+1)+".png";
    else
      file = "imgTesting/anim/000"+std::to_string(i+1)+".png";
    Texture t(file.c_str());
    animList.push_back(t);
  }

  // ground gestion
  std::vector<Sprite> ground;
  for(int i = 0; i < 20; i++){
    Sprite g(Texture("imgTesting/ground.png"), Vector2f(i*200.0f-200.0f,200.0f));
    g.setSize(Vector2f(300.0f,75.0f));
    ground.push_back(g);
  }

  Camera cam(defaultSprite.getPosition(),1.0f);

  Light testLight0(defaultSprite.getPosition(), 0.6f, Vector3i(242,175,90), 0.5f, 0.5f, 0.1f);

  // Main while loop
	while (!glfwWindowShouldClose(window))
	{
    bbopCleanWindow(window, Vector3i(0,0,0),1.0);
   
    //////////////////////////////////////////////////////////////
    ///code zone
    //////////////////////////////////////////////////////////////
    
    cam.setPosition(defaultSprite.getPosition());
    testLight0.setPosition(Vector2f(defaultSprite.getPosition().x+45.0f, defaultSprite.getPosition().y+50.0f));
    defaultScene.addLight(testLight0);
    defaultScene.Use(window);
    defaultScene.useCamera(&cam);
    
    //draw player
    if(animState >= static_cast<int>(animList.size())*5)
      animState = 0;
    defaultSprite.setTexture(animList[animState/5]);
    defaultScene.Draw(defaultSprite);

    //draw ground
    for(size_t i = 0; i < ground.size(); i++){
      defaultScene.Draw(ground[i]);
    }

    //gravity
    if(defaultSprite.getPosition().y+40.0f <= ground[0].getPosition().y)
      defaultSprite.move(Vector2f(0.0f,9.8f));

    //gestiond des mouvement de mario
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
      defaultSprite.move(Vector2f(5.0f,0.0f));   
      animState++;
    } 
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
      defaultSprite.move(Vector2f(-5.0f,0.0f));
      animState++;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
      defaultSprite.move(Vector2f(0.0f,-25.0f));

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

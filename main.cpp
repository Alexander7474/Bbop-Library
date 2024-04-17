////////////////////////////////////////////////////////////////////
//CECI N'EST QU'UN EXEMPLE POUR TESTER SI BBOP EST BIEN INSTALLER
////////////////////////////////////////////////////////////////////
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <string>

#include "include/BBOP/Graphics.h"
#include "include/BBOP/Graphics/bbopFunc.h"
#include "include/BBOP/Graphics/bbopMathClass.h"
#include "include/BBOP/Graphics/textureClass.h"

using namespace std;

int main() {
  
  GLFWwindow * window;
  bbopInit(956,1044,"test",window);
  
  //Creation de la scene pour afficher nos formes
  Scene defaultScene(0.0f,Vector3i(255,255,255));
  //creation d'un rectangle a afficher, par default blanc en haut a gauche de l'image

  Image testImage = bbopLoadPartialImage("imgTesting/anim/00001.png", 4, 0, 0, 400, 300);
  Sprite defaultSprite(Texture(testImage), Vector2f(0.0f,0.0f), Vector3i(255,255,255), Vector2f(50.0f,50.0f));
  defaultSprite.setSize(Vector2f(100.0f,100.0f));
  defaultSprite.flipVertically();
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
  int playerDirection = 0;
  bool playerInMovement = false;
  Vector2f playerMoveVec(0.0f,0.0f);

  // ground gestion
  std::vector<Sprite> ground;
  for(int i = 0; i < 3; i++){
    Sprite g(Texture("imgTesting/ground.png"), Vector2f(i*200.0f-200.0f,200.0f));
    g.setSize(Vector2f(300.0f,75.0f));
    g.flipHorizontally();
    ground.push_back(g);
  }

  Camera cam(defaultSprite.getPosition(),1.0f);

  Light testLight0(defaultSprite.getPosition(), 0.6f, Vector3i(242,175,90), 0.5f, 0.5f, 0.1f);

  Sprite testSprite("imgTesting/noTexture.png");
  testSprite.setSize(50.0f,50.0f);

  defaultSprite.getCollisionBox().setOffsetX(20.0f,20.0f);
  defaultSprite.getCollisionBox().setOffsetY(20.0f,20.0f);
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
    defaultScene.Use();
    defaultScene.useCamera(&cam);
    defaultScene.Draw(testSprite);

    //draw player
    if(animState >= static_cast<int>(animList.size())*5)
      animState = 0;
    defaultScene.Draw(defaultSprite);

    bbopDebugCollisionBox(defaultSprite.getCollisionBox(), defaultScene);
    bbopDebugCollisionBox(testSprite.getCollisionBox(), defaultScene);
    if(defaultSprite.getCollisionBox().check(testSprite.getCollisionBox()))
      std::cout << glfwGetTime() << std::endl;

    //draw ground
    for(size_t i = 0; i < ground.size(); i++){
    }

    //gestion des mouvement
    playerInMovement = false;
    playerMoveVec.x=0.0f;
    if(defaultSprite.getPosition().y+40.0f <= ground[0].getPosition().y && playerMoveVec.y <= -2.0f)
      playerMoveVec.y/=1.15f;
    else if(defaultSprite.getPosition().y+40.0f <= ground[0].getPosition().y && playerMoveVec.y >= -2.0f)
     playerMoveVec.y=9.81f;
    else
     playerMoveVec.y=0.0f;
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
      if(playerDirection != 1){
        playerDirection = 1;
        defaultSprite.flipVertically();
      }
      playerInMovement = true;
    } 
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
      if(playerDirection != 0){
        playerDirection = 0;
        defaultSprite.flipVertically();
      }
      playerInMovement = true;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
      if(defaultSprite.getPosition().y+40.0f >= ground[0].getPosition().y)
        playerMoveVec.y-=25.0f;
    }
    
    if (playerInMovement){
      switch (playerDirection) {
        case 0:   
          playerMoveVec.x-=5.0f;
          animState++;
          break;
        case 1:
          playerMoveVec.x+=5.0f;
          animState++;
          break;
      } 
    }

    defaultSprite.move(playerMoveVec);
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

////////////////////////////////////////////////////////////////////
//CECI N'EST QU'UN EXEMPLE POUR TESTER SI BBOP EST BIEN INSTALLER
////////////////////////////////////////////////////////////////////
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <random>
#include <vector>

#include "include/BBOP/Graphics.h"
#include "include/BBOP/Graphics/bbopGlobal.h"

using namespace std;

int main() {
  
  GLFWwindow * window;
  bbopInit(956,1044,"test",window);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distribx(0, BBOP_WINDOW_SIZE.x);
  uniform_int_distribution<> distriby(0, BBOP_WINDOW_SIZE.y);

  //FPS counter
  int nbFrames = 0;
  //double frameTarget = 1.0/60.0;
  double lastTime = glfwGetTime();
  double fps;
  double currentTime;
  double delta;
  double totalFps = 0.0;
  //FPS end init #######
  // Initialisation Fin ##############################################################################
  Scene defaultScene;
  vector<RectangleShape> rectList;
  RectangleShape driverRect;
  driverRect.setSize(Vector2f(25,25));
  driverRect.setPosition(Vector2f(BBOP_WINDOW_SIZE.x/2.0f,BBOP_WINDOW_SIZE.y/2.0f));
  driverRect.setColor(Vector3i(0,255,0));
  RectangleShape apple;
  apple.setSize(Vector2f(25,25));
  apple.setColor(Vector3i(255,0,0));
  apple.setPosition(Vector2f(distribx(gen),distriby(gen)));
  int direction = 1;
  int TARGET_FPS = 10;
  double lastFrameTime = glfwGetTime();
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
	  // Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
    //////////////////////////////////////////////////////////////
    ///code zone
    //////////////////////////////////////////////////////////////
   defaultScene.Use();
    defaultScene.Draw(driverRect);
    for(int i = (int)rectList.size()-1; i >= 0; i--){
      if (i == 0){
        rectList[i].setPosition(driverRect.getPosition());
      }else {
        rectList[i].setPosition(rectList[i-1].getPosition());
      }
      defaultScene.Draw(rectList[i]);
      if (driverRect.isInCollision(rectList[i].getCollisionBox())){
        break;
      }
    }

    defaultScene.Draw(apple);
    if(glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS){
      direction = 1;
    }else if(glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS){
      direction = 2;
    }else if(glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS){
      direction = 3;
    }else if(glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS){
      direction = 4;
    }

    if (direction == 1){
      driverRect.setPosition(Vector2f(driverRect.getPosition().x,driverRect.getPosition().y-25.0f));

    }else if(direction == 2){
      driverRect.setPosition(Vector2f(driverRect.getPosition().x,driverRect.getPosition().y+25.0f));

    }else if(direction == 3){
      driverRect.setPosition(Vector2f(driverRect.getPosition().x-25.0f,driverRect.getPosition().y));
      
    }else if(direction == 4){
      driverRect.setPosition(Vector2f(driverRect.getPosition().x+25.0f,driverRect.getPosition().y));
    }

    if(driverRect.isInCollision(apple.getCollisionBox())){
      RectangleShape newRect;
      newRect.setSize(Vector2f(25,25));
      newRect.setColor(Vector3i(0,255,0));
      rectList.push_back(newRect);
      apple.setPosition(Vector2f(distribx(gen),distriby(gen)));
    }
    //////////////////////////////////////////////////////////////
    //Check d'erreur
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
      std::cerr << "OpenGL error: " << error << std::endl;
    }
    // Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		 // Calculer le temps écoulé depuis la dernière frame
    double currentFrameTime = glfwGetTime();
    double deltaTime = currentFrameTime - lastFrameTime;

    // Attendre si nécessaire pour atteindre le taux de rafraîchissement cible
    while (deltaTime < 1.0 / TARGET_FPS) {
      glfwWaitEventsTimeout((1.0 / TARGET_FPS - deltaTime) * 0.9); // Attente avec un petit marge
      currentFrameTime = glfwGetTime();
      deltaTime = currentFrameTime - lastFrameTime;
    }
    lastFrameTime = currentFrameTime;
    
    // Take care of all GLFW events
		glfwPollEvents();
	}
	// Delete window before ending the program
	glfwDestroyWindow(window);
  // Terminate GLFW before ending the program
  cout << "Session terminated, avg fps: " << totalFps/glfwGetTime() << endl;
	glfwTerminate();
	return 0;
}

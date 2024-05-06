////////////////////////////////////////////////////////////////////
//CECI N'EST QU'UN EXEMPLE POUR TESTER SI BBOP EST BIEN INSTALLER
////////////////////////////////////////////////////////////////////
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include "include/BBOP/Graphics.h"
#include "include/BBOP/Graphics/fontsClass.h"
#include "include/BBOP/Graphics/spriteClass.h"
#include "include/BBOP/Graphics/textureClass.h"

using namespace std;

int main() {
  
  GLFWwindow * window;
  bbopInit(956,1044,"test",window);

  Scene defaultScene;

  Font font(128, "fonts/arial.ttf");
  TexteBox text("test", &font);

  Sprite spr(Texture("imgTesting/noTexture.png"));

  glfwSwapInterval(0);
  // Main while loop
	while (!glfwWindowShouldClose(window))
	{
    bbopCleanWindow(window, Vector3i(0,0,0),1.0);

   
    //////////////////////////////////////////////////////////////
    ///code zone
    //////////////////////////////////////////////////////////////
    
    defaultScene.Use();
 
    defaultScene.Draw(text);
    defaultScene.Draw(spr);
    
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

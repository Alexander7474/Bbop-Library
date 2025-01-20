/*
 * spriteClass.cpp
 *
 * Ce programme est distribué sous les termes de la Licence Publique
 * Générale GNU, version 3.0, telle que publiée par la Free Software
 * Foundation. Consultez la Licence Publique Générale GNU pour plus de
 * détails.
 *
 * Vous devez avoir reçu une copie de la Licence Publique Générale GNU
 * en même temps que ce programme. Si ce n'est pas le cas, consultez
 * <https://www.gnu.org/licenses/>.
 */

////////////////////////////////////////////////////////////////////
//CECI N'EST QU'UN EXEMPLE POUR TESTER SI BBOP EST BIEN INSTALLER
////////////////////////////////////////////////////////////////////
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include "include/BBOP/Graphics.h"
#include "include/BBOP/Graphics/bbopGlobal.h"
#include "include/BBOP/Graphics/collisionBoxClass.h"
#include "include/BBOP/Graphics/fontsClass.h"
#include "include/BBOP/Graphics/shapeClass.h"


using namespace std;

int main() {
  
  GLFWwindow * window;
  bbopInit(956,1044,"test",window);
  
  //Creation de la scene pour afficher nos formes
  Scene defaultScene(0.4f,Vector3i(255,255,255));

  RectangleShape rect;
  rect.setSize(BBOP_WINDOW_RESOLUTION.x, BBOP_WINDOW_RESOLUTION.y);

  Light light1;
  light1.setPosition(Vector2f(BBOP_WINDOW_RESOLUTION.x/2.f, BBOP_WINDOW_RESOLUTION.y/2.f+100));
  light1.setOpenAngle(3.14f/5.f);
  light1.setColor(Vector3i(255,0,0));

  Light light2;
  light2.setPosition(Vector2f(BBOP_WINDOW_RESOLUTION.x/2.f, BBOP_WINDOW_RESOLUTION.y/2.f));
  light2.setOpenAngle(3.14f/5.f);
  light2.setRotationAngle(M_PI);

	while (!glfwWindowShouldClose(window))
	{
    bbopCleanWindow(window, Vector3i(0,0,0),1.0);

   
    //////////////////////////////////////////////////////////////
    ///code zone
    //////////////////////////////////////////////////////////////
    ///
    defaultScene.addLight(light2);
    defaultScene.addLight(light1);

    defaultScene.Use();

    defaultScene.Draw(rect);
       
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

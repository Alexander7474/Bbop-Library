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
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include "include/BBOP/Graphics.h"
#include "include/BBOP/Graphics/collisionBoxClass.h"


using namespace std;

int main() {
  
  GLFWwindow * window;
  bbopInit(956,1044,"test",window);
  
  //Creation de la scene pour afficher nos formes
  Scene defaultScene(0.0f,Vector3i(255,255,255));

  CollisionBox test;

  test.setPosition(50.f,50.f);
  test.setSize(40.f,40.f);
  test.setOrigin(20.f,20.f);
  test.setOffsetX(-10.f,5.f);
  test.setOffsetY(3.f,-8.f);

  std::cerr << "top: " << test.getTop() << " bottom: " << test.getBottom() << " right: " << test.getRight() << " left: " << test.getLeft() << std::endl; 

	while (!glfwWindowShouldClose(window))
	{
    bbopCleanWindow(window, Vector3i(0,0,0),1.0);

   
    //////////////////////////////////////////////////////////////
    ///code zone
    //////////////////////////////////////////////////////////////
       
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

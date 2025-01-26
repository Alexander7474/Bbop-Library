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
  bbopInit(1920,1080,"name",window);
  
  Scene scene;

  RectangleShape rectangle;
  rectangle.setPosition(100.f, 100.f);
  rectangle.setSize(500.f,500.f);

  while (!glfwWindowShouldClose(window))
  {
    // Nettoyage de la fenêtre
    bbopCleanWindow(window, Vector3i(0,0,0),1.0);

    // On 'active' la scene pour donner au shader opengl les variables uniforms
    scene.Use();

    // Affichage du rectangle
    scene.Draw(rectangle);

    // Faire le rendue du frame buffer de la fenêtre
    scene.render();
    
    // Verfication d'erreur opengl
    bbopErrorCheck();

    // Passage du front buffer pour afficher le rendue opengl sur la fenêtre glfw 
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  // Suppression de la fenêtre
  glfwDestroyWindow(window);
  glfwTerminate();
  
  return 0;
}

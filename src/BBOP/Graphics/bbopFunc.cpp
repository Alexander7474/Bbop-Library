/*
 * bbopFunc.cpp
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

#include "../../../include/BBOP/Graphics/bbopFunc.h"

using namespace std;

int bbopInit(int windowX, int windowY, const char* windowName, GLFWwindow*& window)
{
  //Initialisation Début ############################################################################
  // Initialisation de GLFW
  if (!glfwInit()) {
      cerr << "Échec de l'initialisation de GLFW" << endl;
      return -1;
  }
  // Configuration de GLFW pour utiliser le profil OpenGL Core
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // Création d'une fenêtre GLFW
  window = glfwCreateWindow(windowX, windowY, windowName, nullptr, nullptr);
  if (!window) {
      cerr << "Échec de la création de la fenêtre GLFW" << endl;
      glfwTerminate();
      return -1;
  }
  BBOP_WINDOW_SIZE.x = windowX; BBOP_WINDOW_SIZE.y = windowY;
  BBOP_WINDOW_RESOLUTION.x = windowX; BBOP_WINDOW_RESOLUTION.y = windowY;
  // Définition de la fenêtre comme le contexte OpenGL courant
  glfwMakeContextCurrent(window);
  // Initialisation de GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
      cerr << "Échec de l'initialisation de GLEW" << endl;
      glfwTerminate();
      return -1;
  }
  // Désactiver la synchronisation verticale (V-Sync)
  glfwSwapInterval(1);
  //General info
  cout << "Bbop Engine Version 0.3" << endl << "Author: Alexander74" << endl << "Contact: alexandre.lanternier@outlook.fr" << endl << "License: GPL-3.0" << endl; 
  //GPU info
  const GLubyte* vendor = glGetString(GL_VENDOR);
  const GLubyte* renderer = glGetString(GL_RENDERER);
  cout << "OpenGL Vendor: " << vendor << endl;
  cout << "OpenGL Renderer: " << renderer << endl;
  cout << "Window size: " << BBOP_WINDOW_SIZE.x << "x" << BBOP_WINDOW_SIZE.y << endl;
  cout << "Window resolution: " << BBOP_WINDOW_RESOLUTION.x << "x" << BBOP_WINDOW_RESOLUTION.y << endl;
 
  return 1;
}

void bbopCleanWindow(GLFWwindow*& window, Vector3i rgb, float alpha)
{
  // Specify the color of the background
	glClearColor(rgb.x/255.0f, rgb.y/255.0f, rgb.z/255.0f, alpha);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
  // redimention de la fenêtre
  glfwGetFramebufferSize(window, &BBOP_WINDOW_SIZE.x, &BBOP_WINDOW_SIZE.y);
  glViewport(0, 0, BBOP_WINDOW_SIZE.x, BBOP_WINDOW_SIZE.y);
}

void bbopErrorCheck()
{
  //Check d'erreur
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    std::cerr << "OpenGL error: " << error << std::endl;
  }  
}

void bbopChangeWindowResolution(const Vector2i &nWinR)
{
  BBOP_WINDOW_RESOLUTION = nWinR;
}

void bbopChangeWindowResolution(int x_, int y_)
{
  BBOP_WINDOW_RESOLUTION.x = x_;
  BBOP_WINDOW_RESOLUTION.y = y_;
}

void bbopChangeWindowSize(const Vector2i &nWinS)
{
  BBOP_WINDOW_SIZE = nWinS;
}

void bbopChangeWindowSize(int x_, int y_)
{
  BBOP_WINDOW_SIZE.x = x_;
  BBOP_WINDOW_SIZE.y = y_;
}

void bbopDebugCollisionBox(const CollisionBox &box, Scene& scene)
{
  Vector2f pos_ = box.getPosition();
  pos_.x+=box.getOffsetX().x;pos_.y+=box.getOffsetY().x;
  Vector2f size_ = box.getSize();
  size_.x-=(box.getOffsetX().y+box.getOffsetX().x);size_.y-=(box.getOffsetY().y+box.getOffsetY().x);
  RectangleShape rect(size_,pos_,Vector3i(255,0,0),box.getOrigin());
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  scene.Draw(rect);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


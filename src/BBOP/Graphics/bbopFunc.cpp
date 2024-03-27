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
  cout << "Bbop Engine Version 0.1" << endl << "Author: Alexander74" << endl << "Contact: alexandre.lanternier@outlook.fr" << endl << "License: GPL-3.0" << endl; 
  //GPU info
  const GLubyte* vendor = glGetString(GL_VENDOR);
  const GLubyte* renderer = glGetString(GL_RENDERER);
  cout << "OpenGL Vendor: " << vendor << endl;
  cout << "OpenGL Renderer: " << renderer << endl;
  cout << "Window size: " << BBOP_WINDOW_SIZE.x << "x" << BBOP_WINDOW_SIZE.y << endl;
 
  return 1;
}

void bbopCleanWindow(GLFWwindow*& window, Vector3i rgb, float alpha)
{
  // Specify the color of the background
	glClearColor(rgb.x/255.0f, rgb.y/255.0f, rgb.z/255.0f, alpha);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
  // redimention de la fenêtre
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
}

void bbopErrorCheck()
{
  //Check d'erreur
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    std::cerr << "OpenGL error: " << error << std::endl;
  }  
}

void bbopChangeWindowSize(Vector2i nWinSize)
{
  BBOP_WINDOW_SIZE = nWinSize;
}

void bbopDebugCollisionBox(CollisionBox* box, Scene& scene)
{
  RectangleShape rect(box->getSize(),box->getPosition(),Vector3i(255,0,0),box->getOrigin());
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  scene.Draw(rect);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

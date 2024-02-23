#ifndef GLOBALS_H
#define GLOBALS_H

#include "bbopMathClass.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
#include<fstream>

using namespace std;

extern int BBOP_SHADER_MODE_TEXTURE;
extern int BBOP_SHADER_MODE_COLOR;
extern int BBOP_SHADER_MODE_MIX;
extern Vector2i BBOP_WINDOW_SIZE;

int bbopInit(int windowX, int windowY, const char* windowName, GLFWwindow*& window);
void bbopCleanWindow();
void bbopErrorCheck();
string getFileData(const char* filename);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void bbopChangeWindowSize();

class BbopDrawable
{
public:
  virtual void Draw(GLint renderModeLoc) const = 0;
};

#endif // ! GLOBALS_H

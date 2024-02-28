#ifndef BBOP_FUNCTION_H
#define BBOP_FUNCTION_H

#include "bbopMathClass.h"
#include "bbopGlobal.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int bbopInit(int windowX, int windowY, const char* windowName, GLFWwindow*& window);
void bbopCleanWindow(Vector3i rgb, float alpha);
void bbopErrorCheck();
void bbopChangeWindowSize();

#endif // !BBOP_FUNCTION_H

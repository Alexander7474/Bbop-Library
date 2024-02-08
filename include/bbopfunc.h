#ifndef BBOP_FUNC_H
#define BBOP_FUNC_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include<fstream>

using namespace std;

string getFileData(const char* filename);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif //!BBOP_FUNC_H

#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <variant>
#include <vector>

#include "spriteClass.h"
#include "shaderClass.h"
#include "bbopGlobal.h"

using namespace std;

class Scene
{
public:
  Scene();

  void Use();
  void Delete();
  void Draw(BbopDrawable& spr);
private:
  Shader sceneShader;
  GLfloat ambiantLightValue;
  GLint ambiantLightLoc;
  GLint renderModeLoc;
};

#endif // !SCENE_CLASS_H

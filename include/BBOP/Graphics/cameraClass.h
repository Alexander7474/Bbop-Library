#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "bbopGlobal.h"
#include "bbopMathClass.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Camera 
{
public:
  Camera(Vector2f nPos, float nScale);
  Camera();

  void buildCamera();
  void setScale(float nScale);
  float getScale();
  void setPosition(Vector2f nPos);
  Vector2f getPosition();
  void setOrigin(Vector2f nOrigin);
  Vector2f getOrigin();
  Vector2f camX;
  Vector2f camY;
private:
  Vector2f origin;
  Vector2f pos;
  float scale;
};

#endif // !CAMERA_CLASS_H

#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "bbopMathClass.h"
#include "bbopGlobal.h"

class LightPoint: public BbopDrawable
{
public:
  LightPoint(Vector2f nPos, float nPower);

  void setPosition(Vector2f nPos);
  Vector2f getPosition();
  void setPower(float nPower);
  float getPower();
  void Draw(GLint renderModeLoc) const override;
private:
  float lightPower;
  Vector2f pos;
};

#endif // ! LIGHT_CLASS_H

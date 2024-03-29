#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "bbopMathClass.h"
#include "bbopGlobal.h"

/**
 * @class Light
 * @brief Gère un point de lumière
 */
class Light
{
public:
  Light(Vector2f nPos, float nIntensity, Vector3i nRGB, float nConstantAttenuation,float nLinearAttenuation, float nQuadraticAttenuation);

  Vector3i getColor();
  void setColor(Vector3i nRGB);
  Vector2f getPosistion();
  void setPosition(Vector2f nPos);
  float getIntensity();
  void setIntensity(float nIntensity);
  float getConstant();
  void setConstant(float nConstant);
  float getLinear();
  void setLinear(float nLinear);
  float getQuadratic();
  void setQuadratic(float nQuadratic);
private:
  Vector2f pos;
  Vector3i RGB; // Couleur de la lumière
  float intensity; // Intensité de la lumière
  float constantAttenuation; // Attnuation constante
  float linearAttenuation; // Attnuation linéaire
  float quadraticAttenuation; // Attnuation quadratique
};

#endif // ! LIGHT_CLASS_H

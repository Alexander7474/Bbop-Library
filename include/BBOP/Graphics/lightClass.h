#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "bbopMathClass.h"
#include "bbopGlobal.h"

class Light
{
public:
  Light(Vector2f nPos, float nIntensity, Vector3i nRGB, float nConstantAttenuation,float nLinearAttenuation, float nQuadraticAttenuation);

private:
  Vector2f pos;
  Vector3i RGB; // Couleur de la lumière
  float intensity; // Intensité de la lumière
  float constantAttenuation; // Attnuation constante
  float linearAttenuation; // Attnuation linéaire
  float quadraticAttenuation; // Attnuation quadratique
};

#endif // ! LIGHT_CLASS_H

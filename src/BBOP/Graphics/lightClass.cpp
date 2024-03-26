#include "../../../include/BBOP/Graphics/lightClass.h"


Light::Light(Vector2f nPos, float nIntensity, Vector3i nRGB, float nConstantAttenuation,float nLinearAttenuation, float nQuadraticAttenuation)
  : pos(nPos),
    RGB(nRGB),
    intensity(nIntensity),
    constantAttenuation(nConstantAttenuation),
    linearAttenuation(nLinearAttenuation),
    quadraticAttenuation(nQuadraticAttenuation)
{}

Vector2f Light::getPosistion()
{
  return pos;
}

void Light::setPosition(Vector2f nPos)
{
  pos = nPos;
}

Vector3i Light::getColor()
{
  return RGB;
}

void Light::setColor(Vector3i nRGB)
{
  RGB = nRGB;
}

float Light::getIntensity()
{
  return intensity;
}

void Light::setIntensity(float nIntensity)
{
  intensity = nIntensity;
}

float Light::getLinear()
{
  return linearAttenuation;
}

void Light::setLinear(float nLinear)
{
  linearAttenuation = nLinear;
}

float Light::getConstant()
{
  return constantAttenuation;
}

void Light::setConstant(float nConstant)
{
  constantAttenuation = nConstant;
}

float Light::getQuadratic()
{
  return quadraticAttenuation;
}

void Light::setQuadratic(float nQuadratic)
{
  quadraticAttenuation = nQuadratic;
}

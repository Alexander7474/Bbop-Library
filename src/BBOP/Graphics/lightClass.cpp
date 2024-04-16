/*
 * lightClass.cpp
 *
 * Ce programme est distribué sous les termes de la Licence Publique
 * Générale GNU, version 3.0, telle que publiée par la Free Software
 * Foundation. Consultez la Licence Publique Générale GNU pour plus de
 * détails.
 *
 * Vous devez avoir reçu une copie de la Licence Publique Générale GNU
 * en même temps que ce programme. Si ce n'est pas le cas, consultez
 * <https://www.gnu.org/licenses/>.
 */

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

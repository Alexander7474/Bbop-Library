#include "../../../include/BBOP/Graphics/lightClass.h"


Light::Light(Vector2f nPos, float nIntensity, Vector3i nRGB, float nConstantAttenuation,float nLinearAttenuation, float nQuadraticAttenuation)
  : pos(nPos),
    RGB(nRGB),
    intensity(nIntensity),
    constantAttenuation(nConstantAttenuation),
    linearAttenuation(nLinearAttenuation),
    quadraticAttenuation(nQuadraticAttenuation)
{}

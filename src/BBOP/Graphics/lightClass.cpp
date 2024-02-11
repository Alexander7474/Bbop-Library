#include "../../../include/BBOP/Graphics/lightClass.h"

LightPoint::LightPoint(Vector2f nPos, float nPower)
  : pos(nPos.x, nPos.y),
    lightPower(nPower)
{}

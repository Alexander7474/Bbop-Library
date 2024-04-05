#include "../../../include/BBOP/Graphics/geometricClass.h"


Geometric::Geometric(Vector2f nPos, Vector2f nOrigin, Vector2f nSize, float nRotation): pos(nPos.x ,nPos.y), origin(nOrigin.x, nOrigin.y), size(nSize.x, nSize.y), rotation(nRotation) {}

void Geometric::setPosition(const Vector2f &nPos)
{
  pos = nPos;
}

const Vector2f &Geometric::getPosition() const
{
  return pos;
}

void Geometric::setSize(const Vector2f &nSize)
{
  size = nSize;
}

const Vector2f &Geometric::getSize() const 
{
  return size;
}

void Geometric::setOrigin(const Vector2f &nOrigin)
{
  origin = nOrigin;
}

const Vector2f &Geometric::getOrigin() const 
{
  return origin;
}

void Geometric::setRotation(float nRotation)
{
  rotation = nRotation;
}

float Geometric::getRotation() const
{
  return rotation;
}


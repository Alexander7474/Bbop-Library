#ifndef GEOMETRIC_CLASS_H
#define GEOMETRIC_CLASS_H

#include "bbopMathClass.h"
#include <iostream>

/**
 * @class Geometric
 * @brief gère un objet avec de propriété géométrique
 *
 * @note Class utile pour décrire toute forme géometrique
 */
class Geometric 
{
public:
  Geometric(Vector2f nPos, Vector2f nOrigin, Vector2f nSize, float nRotation);

  void setPosition(const Vector2f &nPos);
  const Vector2f &getPosition() const;
  void setSize(const Vector2f &nSize);
  const Vector2f &getSize() const;
  void setOrigin(const Vector2f &nOrigin);
  const Vector2f &getOrigin() const;
  void setRotation(float nRotation);
  float getRotation() const;

protected:
  Vector2f pos;
  Vector2f origin;
  Vector2f size;
  float rotation;
};


#endif // !GEOMETRIC_CLASS_H

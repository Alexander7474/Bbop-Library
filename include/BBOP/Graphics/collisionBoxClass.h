#ifndef COLLISION_BOX_CLASS_H
#define COLLISION_BOX_CLASS_H

#include "bbopMathClass.h"
#include <iostream>

/**
 * @class CollisionBox
 * @brief gère une boîte de collision
 *
 * @note Cette class est utilisé par défault pour gèrer les collision des Shape
 */
class CollisionBox 
{
public:
  CollisionBox(Vector2f nPos, Vector2f nOrigin, Vector2f nSize, float nRotation);

  void setPosition(Vector2f nPos);
  Vector2f getPosition();
  void setSize(Vector2f nSize);
  Vector2f getSize();
  void setOrigin(Vector2f nOrigin);
  Vector2f getOrigin();
  void setRotation(float nRotation);
  float getRotation();
  bool check(CollisionBox* otherBox);
  bool checkWithRotation(CollisionBox * otherBox);
private:
  Vector2f pos;
  Vector2f origin;
  Vector2f size;
  float rotation;
};


#endif // !COLLISION_BOX_CLASS_H

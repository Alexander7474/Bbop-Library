#ifndef COLLISION_BOX_CLASS_H
#define COLLISION_BOX_CLASS_H

#include "bbopMathClass.h"
#include <iostream>

using namespace std;

class CollisionBox 
{
public:
  CollisionBox(Vector2f nPos, Vector2f nOrigin, Vector2f nSize);

  void setPosition(Vector2f nPos);
  Vector2f getPosition();
  void setSize(Vector2f nSize);
  Vector2f getSize();
  void setOrigin(Vector2f nOrigin);
  Vector2f getOrigin();
  void move(Vector2f vecM);
  bool check(CollisionBox* box);
private:
  Vector2f pos;
  Vector2f origin;
  Vector2f size;
};


#endif // !COLLISION_BOX_CLASS_H

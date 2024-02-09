#ifndef COLLISION_BOX_CLASS_H
#define COLLISION_BOX_CLASS_H

#include <iostream>

using namespace std;

class CollisionBox 
{
public:
  CollisionBox();

  void setPosition(float nx, float ny);
  float getPositionX();
  float getPositionY();
  void setSize(float nWidth, float nHeight);
  float getWidth();
  float getHeight();
  void setOrigin(float nOriginX, float nOriginY);
  float getOriginX();
  float getOriginY();
  void init(float nx, float ny, float nwidth, float nheight, float noriginX, float noriginY);
  bool check(CollisionBox* box);
private:
  float width;
  float height;
  float x;
  float y;
  float originX;
  float originY;
};


#endif // !COLLISION_BOX_CLASS_H

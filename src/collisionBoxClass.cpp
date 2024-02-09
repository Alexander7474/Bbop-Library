#include "../include/collisonBoxClass.h"

CollisionBox::CollisionBox()
{
  x = 0.0f;
  y = 0.0f;
  width = 0.0f;
  height = 0.0f;
  originX = 0.0f;
  originY = 0.0f;
}

void CollisionBox::init(float nx, float ny, float nwidth, float nheight, float noriginX, float noriginY)
{
  x = nx;
  y = ny;
  width = nwidth;
  height = nheight;
  originX = noriginX;
  originY = noriginY;
}

bool CollisionBox::check(CollisionBox* box)
{
  //cout << x << ";" << y << " " << width << ";" << height <<  endl << box->getPositionX() << ";" << box->getPositionY() << endl;
  if (x <= box->getPositionX() && box->getPositionX() <= x+width && y <= box->getPositionY() && box->getPositionY() <= y+height){
    return true;
  }
  if (x <= box->getPositionX()+box->getWidth() && box->getPositionX()+box->getWidth() <= x+width && y <= box->getPositionY() && box->getPositionY() <= y+height){
    return true;
  }
  if (x <= box->getPositionX() && box->getPositionX() <= x+width && y <= box->getPositionY()+box->getHeight() && box->getPositionY()+box->getHeight() <= y+height){
    return true;
  }
  if (x <= box->getPositionX()+box->getWidth() && box->getPositionX()+box->getWidth() <= x+width && y <= box->getPositionY()+box->getHeight() && box->getPositionY()+box->getHeight() <= y+height){
    return true;
  }
  return false;
}

void CollisionBox::setPosition(float nx, float ny)
{
  x = nx;y = ny; 
}

float CollisionBox::getPositionX()
{
  return x;
}

float CollisionBox::getPositionY()
{
  return y;
}

void CollisionBox::setSize(float nWidth, float nHeight)
{
  width = nWidth;height = nHeight;
}

float CollisionBox::getWidth()
{
  return width;
}

float CollisionBox::getHeight()
{
  return height;
}

void CollisionBox::setOrigin(float nOriginX, float nOriginY)
{
  originX = nOriginX;originY = nOriginY; 
}

float CollisionBox::getOriginX()
{
  return originX;
}

float CollisionBox::getOriginY()
{
  return originY;
}

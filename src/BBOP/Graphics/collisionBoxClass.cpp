#include "../../../include/BBOP/Graphics/collisonBoxClass.h"

CollisionBox::CollisionBox(Vector2f nPos, Vector2f nOrigin, Vector2f nSize): pos(nPos.x ,nPos.y), origin(nOrigin.x, nOrigin.y), size(nSize.x, nSize.y) {}

bool CollisionBox::check(CollisionBox* box)
{
  //cout << x << ";" << posY << " " << size.x << ";" << size.y <<  endl << otherBoxX << ";" << otherBoxY << endl;
  float posX = pos.x-origin.x; float posY = pos.y-origin.y;
  float otherBoxX = box->getPosition().x-box->getOrigin().x;float otherBoxY = box->getPosition().y-box->getOrigin().y;
  if (posX <= otherBoxX && otherBoxX <= posX+size.x && posY <= otherBoxY && otherBoxY <= posY+size.y){
    return true;
  }
  if (posX <= otherBoxX+box->getSize().x && otherBoxX+box->getSize().x <= posX+size.x && posY <= otherBoxY && otherBoxY <= posY+size.y){
    return true;
  }
  if (posX <= otherBoxX && otherBoxX <= posX+size.x && posY <= otherBoxY+box->getSize().y && otherBoxY+box->getSize().y <= posY+size.y){
    return true;
  }
  if (posX <= otherBoxX+box->getSize().x && otherBoxX+box->getSize().x <= posX+size.x && posY <= otherBoxY+box->getSize().y && otherBoxY+box->getSize().y <= posY+size.y){
    return true;
  }
  return false;
}

void CollisionBox::setPosition(Vector2f nPos)
{
  pos = nPos;
}

Vector2f CollisionBox::getPosition()
{
  return pos;
}

void CollisionBox::setSize(Vector2f nSize)
{
  size = nSize;
}

Vector2f CollisionBox::getSize()
{
  return size;
}

void CollisionBox::setOrigin(Vector2f nOrigin)
{
  origin = nOrigin;
}

Vector2f CollisionBox::getOrigin()
{
  return origin;
}


#include "../include/collisonBoxClass.h"

CollisionBox::CollisionBox(Vector2f nPos, Vector2f nOrigin, Vector2f nSize): pos(nPos.x ,nPos.y), origin(nOrigin.x, nOrigin.y), size(nSize.x, nSize.y) {}

bool CollisionBox::check(CollisionBox* box)
{
  //cout << x << ";" << posY << " " << size.x << ";" << size.y <<  endl << box->getPosition().x << ";" << box->getPosition().y << endl;
  float posX = pos.x-origin.x; float posY = size.y-origin.y;
  if (posX <= box->getPosition().x && box->getPosition().x <= posX+size.x && posY <= box->getPosition().y && box->getPosition().y <= posY+size.y){
    return true;
  }
  if (posX <= box->getPosition().x+box->getPosition().x && box->getPosition().x+box->getPosition().x <= posX+size.x && posY <= box->getPosition().y && box->getPosition().y <= posY+size.y){
    return true;
  }
  if (posX <= box->getPosition().x && box->getPosition().x <= posX+size.x && posY <= box->getPosition().y+box->getPosition().y && box->getPosition().y+box->getPosition().y <= posY+size.y){
    return true;
  }
  if (posX <= box->getPosition().x+box->getPosition().x && box->getPosition().x+box->getPosition().x <= posX+size.x && posY <= box->getPosition().y+box->getPosition().y && box->getPosition().y+box->getPosition().y <= posY+size.y){
    return true;
  }
  return false;
}

void CollisionBox::setPosition(Vector2f nPos)
{
  pos.x = nPos.x;pos.y = nPos.y; 
}

Vector2f CollisionBox::getPosition()
{
  return pos;
}

void CollisionBox::setSize(Vector2f nSize)
{
  size.x = nSize.x;size.y = nSize.y;
}

Vector2f CollisionBox::getSize()
{
  return size;
}

void CollisionBox::setOrigin(Vector2f nOrigin)
{
  origin.x = nOrigin.x;origin.y = nOrigin.y; 
}

Vector2f CollisionBox::getOrigin()
{
  return origin;
}

void CollisionBox::move(Vector2f vecM)
{
  pos.x += vecM.x; pos.y += vecM.y;
}


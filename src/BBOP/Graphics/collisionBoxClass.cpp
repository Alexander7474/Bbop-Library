#include "../../../include/BBOP/Graphics/collisonBoxClass.h"
#include <cmath>

#include <iostream>
using namespace std;

CollisionBox::CollisionBox(Vector2f nPos, Vector2f nOrigin, Vector2f nSize, float nRotation): pos(nPos.x ,nPos.y), origin(nOrigin.x, nOrigin.y), size(nSize.x, nSize.y), rotation(nRotation) {}

bool CollisionBox::check(CollisionBox* otherBox)
{
  //cout << x << ";" << posY << " " << size.x << ";" << size.y <<  endl << otherBoxX << ";" << otherBoxY << endl;
  float left = pos.x-origin.x; float right = left+size.x;
  float top = pos.y-origin.y;float bottom = top+size.y;
  float otherLeft = otherBox->getPosition().x-otherBox->getOrigin().x;float otherRight = otherLeft+otherBox->getSize().x;
  float otherTop = otherBox->getPosition().y-otherBox->getOrigin().y;float otherBottom = otherTop+otherBox->getSize().y;
  if (left > otherRight || right < otherLeft || top > otherBottom || bottom < otherTop){
    return false;
  }
  return true;
}

bool CollisionBox::checkWithRotation(CollisionBox *otherBox)
{
  //cout << x << ";" << posY << " " << size.x << ";" << size.y <<  endl << otherBoxX << ";" << otherBoxY << endl;
  Vector2f boxMiddle(pos.x-origin.x+(size.x/2.0f),pos.y-origin.y+(size.y/2.0f));
  Vector2f otherBoxMiddle(otherBox->pos.x-otherBox->origin.x+(otherBox->size.x/2.0f),otherBox->pos.y-otherBox->origin.y+(otherBox->size.y/2.0f));
  float c = cos(rotation);
  float s = sin(rotation);
  float otherCos = cos(otherBox->rotation);
  float otherSin = sin(otherBox->rotation);
  Vector2f translated(boxMiddle.x-pos.x,boxMiddle.y-pos.y);
  Vector2f otherTranslated(otherBoxMiddle.x-otherBox->getPosition().x,otherBoxMiddle.y-otherBox->getPosition().y);
  Vector2f final(translated.x*c-translated.y*s,translated.x*s+translated.y*c);
  Vector2f otherFinal(otherTranslated.x*otherCos-otherTranslated.y*otherSin,otherTranslated.x*otherSin+otherTranslated.y*otherCos);
  final.x+=pos.x;final.y+=pos.y;
  otherFinal.x+=otherBox->getPosition().x;otherFinal.y+=otherBox->getPosition().y;
  float left = final.x-(size.x/2.0f); float right = left+size.x;
  float top = pos.y-(size.y/2.0f);float bottom = top+size.y;
  float otherLeft = otherFinal.x-(otherBox->getSize().x/2.0f);float otherRight = otherLeft+otherBox->getSize().x;
  float otherTop = otherFinal.y-(otherBox->getSize().y/2.0f);float otherBottom = otherTop+otherBox->getSize().y;
  if (left > otherRight || right < otherLeft || top > otherBottom || bottom < otherTop){
    return false;
  }
  return true;
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

void CollisionBox::setRotation(float nRotation)
{
  rotation = nRotation;
}

float CollisionBox::getRotation()
{
  return rotation;
}


#include "../../../include/BBOP/Graphics/cameraClass.h"

Camera::Camera()
  : camX(0.0f,0.0f),
    camY(0.0f,0.0f),
    pos(BBOP_WINDOW_SIZE.x/2.0f,BBOP_WINDOW_SIZE.y/2.0f),
    scale(1.0f)
{
  buildCamera();
}

Camera::Camera(Vector2f nPos, float nScale)
  : camX(0.0f,0.0f),
    camY(0.0f,0.0f),
    pos(nPos),
    scale(nScale)
{
  buildCamera();
}

void Camera::buildCamera()
{
  camX.x = pos.x-scale*(BBOP_WINDOW_SIZE.x/2.0f);
  camX.y = pos.x+scale*(BBOP_WINDOW_SIZE.x/2.0f);
  camY.x = pos.y-scale*(BBOP_WINDOW_SIZE.y/2.0f);
  camY.y = pos.y+scale*(BBOP_WINDOW_SIZE.y/2.0f);
}

void Camera::setPosition(Vector2f nPos)
{
  pos = nPos;
  buildCamera();
}

Vector2f Camera::getPosition()
{
  return pos;
}

void Camera::setScale(float nScale)
{
  scale = nScale;
  buildCamera();
}

float Camera::getScale()
{
  return scale;
}

Vector2f Camera::screenPosToCamPos(Vector2f screenPos)
{
  Vector2f finalPos(pos.x-scale*(BBOP_WINDOW_SIZE.x/2.0f),pos.y-scale*(BBOP_WINDOW_SIZE.y/2.0f));
  finalPos.x += screenPos.x*scale;
  finalPos.y += screenPos.y*scale;
  return finalPos;
}

//ne marche que avec les formes rectangulaires
bool Camera::isInCamView(Shape& obj)
{
  float left = obj.getPosition().x-obj.getOrigin().x;
  float right = left+obj.getSize().x;
  float top = obj.getPosition().y-obj.getOrigin().y;
  float bottom = top+obj.getSize().y;
  if(right<=camX.x || left >= camX.y || top >= camY.y || bottom <= camY.x){
    return false;
  }
  return true;
}


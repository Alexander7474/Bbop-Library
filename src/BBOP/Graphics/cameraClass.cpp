#include "../../../include/BBOP/Graphics/cameraClass.h"

Camera::Camera()
  : camX(0.0f,0.0f),
    camY(0.0f,0.0f),
    origin(BBOP_WINDOW_SIZE.x/2.0f,BBOP_WINDOW_SIZE.y/2.0f),
    pos(BBOP_WINDOW_SIZE.x/2.0f,BBOP_WINDOW_SIZE.y/2.0f),
    scale(1.0f)
{
  buildCamera();
}

Camera::Camera(Vector2f nPos, float nScale)
  : camX(0.0f,0.0f),
    camY(0.0f,0.0f),
    origin((BBOP_WINDOW_SIZE.x/2.0f)*nScale,(BBOP_WINDOW_SIZE.y/2.0f)*nScale),
    pos(nPos),
    scale(nScale)
{
  buildCamera();
}

void Camera::buildCamera()
{
  camX.x = scale*(pos.x-origin.x);
  camX.y = scale*(pos.x+BBOP_WINDOW_SIZE.x-origin.x);
  camY.x = scale*(pos.y-origin.y);
  camY.y = scale*(pos.y+BBOP_WINDOW_SIZE.y-origin.y);
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

void Camera::setOrigin(Vector2f nOrigin)
{
  origin = nOrigin;
  buildCamera();
}

Vector2f Camera::getOrigin()
{
  return origin;
}

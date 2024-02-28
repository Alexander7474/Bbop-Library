#include "../../../include/BBOP/Graphics/bbopMathClass.h"

Vector2f::Vector2f(float nx, float ny): x(nx), y(ny){}
Vector2f::Vector2f(): x(0.0f), y(0.0f){}
Vector2d::Vector2d(double nx, double ny): x(nx), y(ny){}
Vector2d::Vector2d(): x(0.0), y(0.0){}
Vector2i::Vector2i(int nx, int ny): x(nx), y(ny){}
Vector2i::Vector2i(): x(0), y(0){}
Vector3i::Vector3i(int nx, int ny, int nz): x(nx), y(ny), z(nz){}
Vector3i::Vector3i(): x(0), y(0), z(0){}
Vector3f::Vector3f(float nx, float ny, float nz): x(nx), y(ny), z(nz){}
Vector3f::Vector3f(): x(0.0f), y(0.0f), z(0.0f){}
Vector3d::Vector3d(double nx, double ny, double nz): x(nx), y(ny), z(nz){}
Vector3d::Vector3d(): x(0.0), y(0.0), z(0.0){}
//Vector4i::Vector4i(int nx, int ny, int nz, int nw): x(nx), y(ny), z(nz), w(nw){}
//Vector4f::Vector4f(float nx, float ny, float nz, float nw): x(nx), y(ny), z(nz), w(nw){}
//Vector4d::Vector4d(double nx, double ny, double nz, double nw): x(nx), y(ny), z(nz), w(nw){}

Vector2f rotatePoint(Vector2f point, Vector2f origin, float angle)
{
  float c = cos(angle);
  float s = sin(angle);
  // translate point back to origin:
  point.x -= origin.x;
  point.y -= origin.y;

  // rotate point
  float xnew = point.x * c - point.y * s;
  float ynew = point.x * s + point.y * c;

  // translate point back:
  point.x = xnew + origin.x;
  point.y = ynew + origin.y;
  return point;
}


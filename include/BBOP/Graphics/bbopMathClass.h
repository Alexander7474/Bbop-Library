#ifndef MATH_CLASS_H
#define MATH_CLASS_H

class Vector2i
{
public:
  int x;
  int y;

  Vector2i(int nx, int ny);
};

class Vector2f
{
public:
  float x;
  float y;

  Vector2f(float nx, float ny);
};

class Vector2d
{
public:
  double x;
  double y;

  Vector2d(double nx, double ny);
};

class Vector3i
{
public:
  int x,y,z;
  Vector3i(int nx, int ny, int nz);
};

#endif // ! MATH_CLASS_H

#include "../../../include/BBOP/Graphics/bbopMathClass.h"

template<typename T>
Vector2<T>::Vector2() : x(T()), y(T()) {}

template<typename T>
Vector2<T>::Vector2(T x_, T y_) : x(x_), y(y_) {}

// Implémentation de la classe Vector2i
Vector2i::Vector2i() : Vector2<int>() {}

Vector2i::Vector2i(int x_, int y_) : Vector2<int>(x_, y_) {}

// Implémentation de la classe Vector2f
Vector2f::Vector2f() : Vector2<float>() {}

Vector2f::Vector2f(float x_, float y_) : Vector2<float>(x_, y_) {}

// Implémentation de la classe Vector2d
Vector2d::Vector2d() : Vector2<double>() {}

Vector2d::Vector2d(double x_, double y_) : Vector2<double>(x_, y_) {}

template<typename T>
Vector3<T>::Vector3() : x(T()), y(T()), z(T()) {}

template<typename T>
Vector3<T>::Vector3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

// Implémentation de la classe Vector3i
Vector3i::Vector3i() : Vector3<int>() {}

Vector3i::Vector3i(int x_, int y_, int z_) : Vector3<int>(x_, y_, z_) {}

// Implémentation de la classe Vector3d
Vector3f::Vector3f() : Vector3<float>() {}

Vector3f::Vector3f(float x_, float y_, float z_) : Vector3<float>(x_, y_, z_) {}

// Implémentation de la classe Vector3d
Vector3d::Vector3d() : Vector3<double>() {}

Vector3d::Vector3d(double x_, double y_, double z_) : Vector3<double>(x_, y_, z_) {}

template<typename T>
Vector4<T>::Vector4() : x(T()), y(T()), z(T()), w(T()) {}

template<typename T>
Vector4<T>::Vector4(T x_, T y_, T z_, T w_) : x(x_), y(y_), z(z_), w(w_) {}


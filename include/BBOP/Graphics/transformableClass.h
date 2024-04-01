#ifndef TRANSFORMABLE_CLASS_H
#define TRANSFORMABLE_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "bbopMathClass.h"

/**
 * @class Transformable
 * @brief class parente pour tous objet transformable
 * 
 * @see Shape CollisionBox TexteBox
 * @todo Implenter a Shape et la scale
 */
class Transformable 
{
public: 
  Transformable();
  ~Transformable();

   /**
   * @brief Renvoie la Taille du Shape
   *
   * @return size taille
   */
  const Vector2f &getSize() const;

  /**
   * @brief Change la taille du Shape 
   *
   * @param[in] nSize taille
   */
  void setSize(const Vector2f &nSize);

  /**
   * @brief Change la taille du Shape 
   *
   * @param[in] x_ taille x
   * @param[in] y_ taille y
   */
  void setSize(float x_, float y_);

  /**
   * @brief Renvoie la position du Shape
   *
   * @return pos position
   */
  const Vector2f &getPosition() const;

  /**
   * @brief Change la position du Shape 
   *
   * @param[in] nPos position
   */
  void setPosition(const Vector2f &nPos);

  /**
   * @brief Change la position de la Shape
   *
   * @param[in] x_ position x
   * @param[in] y_ position y
   */
  void setPosition(float x_, float y_);

  /**
   * @brief Renvoie l'origine de la Shape 
   *
   * @return origin
   */
  const Vector2f &getOrigin() const;

  /**
   * @brief Change l'origine de la Shape 
   *
   * @param[in] nOrigin origin 
   */
  void setOrigin(const Vector2f &nOrigin);

  /**
   * @brief Change l'origine de la Shape 
   *
   * @param[in] x_ origine x
   * @param[in] y_ origine y
   */
  void setOrigin(float x_, float y_);

private:
  Vector2f size;
  Vector2f scale;
  Vector2f pos;
  Vector2f origin;
  float rotation;
};

#endif // ! TRANSFORMABLE_CLASS_H

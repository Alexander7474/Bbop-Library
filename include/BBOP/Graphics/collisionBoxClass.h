#ifndef COLLISION_BOX_CLASS_H
#define COLLISION_BOX_CLASS_H

#include "bbopMathClass.h"
#include <iostream>

/**
 * @class CollisionBox
 * @brief gère une boîte de collision
 *
 * @note Cette class est utilisé par défault pour gèrer les collision des Shape
 */
class CollisionBox 
{
public:
  /**
  * @brief Constructeur de la boîte de collision 
  *
  * @param[in] nPos position de la boîte
  * @param[in] nOrigin origin de la boîte 
  * @param[in] nSize Dimension de la boîte 
  * @param[in] nRotation angle de rotation de la boîte 
  */
  CollisionBox(Vector2f nPos, Vector2f nOrigin, Vector2f nSize, float nRotation);

  void setPosition(const Vector2f &nPos);
  const Vector2f &getPosition() const;
  void setSize(const Vector2f &nSize);
  const Vector2f &getSize() const;
  void setOrigin(const Vector2f &nOrigin);
  const Vector2f &getOrigin() const;
  void setRotation(float nRotation);
  float getRotation() const;

  /**
  * @brief Detecte si la boîte est en collision avec une autre
  *
  * @param[in] otherBox Boîte à comparer avec la boîte qui appele la méthode
  * @return bool true si la boîte est en collision avec otherBox et false si non
  *
  * @attenion Cette méthode ne prend pas en compte la roation des deux boîte pour des raisons de performances
  */
  bool check(const CollisionBox &otherBox) const;

  /**
  * @brief Detecte si la boîte est en collision en prenant en compte la rotaion des deux boîtes
  *
  * @param[in] otherBox Boîte à comparer avec la boîte qui appele la méthode 
  * @return bool true si la boîte est en collision avec otherBox et false si non
  *
  * @attenion Cette méthode prend en compte la rotation et est donc plus gourmand en ressource, à utiliser seulement si nécessaire
  */
  bool checkWithRotation(const CollisionBox &otherBox) const;

private:
  Vector2f pos;
  Vector2f origin;
  Vector2f size;
  float rotation;
};


#endif // !COLLISION_BOX_CLASS_H

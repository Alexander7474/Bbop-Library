#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "bbopMathClass.h"
#include "bbopGlobal.h"

/**
 * @class Light
 * @brief Gère un point de lumière en fonction de son Intensité, sa couleur et son attenuation
 */
class Light
{
public:

  /**
  * @brief Constructeur de light 
  *
  * @param[in] nPos Position
  * @param[in] nIntensity Intensité
  * @param[in] nRGB couleur
  * @param[in] nConstantAttenuation attenuation constante 
  * @param[in] nLinearAttenuation attenuation linéaire 
  * @param[in] nQuadraticAttenuation attenuation quadratique
  */
  Light(Vector2f nPos, float nIntensity, Vector3i nRGB, float nConstantAttenuation,float nLinearAttenuation, float nQuadraticAttenuation);

  /**
  * @brief Renvoie la couleur de Light
  *
  * @return RGB
  */
  Vector3i getColor();

  /**
   * @brief Change la couleur de Light
   *
   * @param[in] nRGB Couleur
   */
  void setColor(Vector3i nRGB);
  
  /**
  * @brief Renvoie la position de Light
  *
  * @return pos
  */
  Vector2f getPosistion();

  /**
   * @brief Change la position de Light
   *
   * @param[in] nPos Position
   */
  void setPosition(Vector2f nPos);
  
  /**
  * @brief Renvoie l'Intensité de Light
  *
  * @return intensity
  */
  float getIntensity();

  /**
   * @brief Change l'Intensité de Light
   *
   * @param[in] nIntensity Intensité
   */
  void setIntensity(float nIntensity);
  
  /**
  * @brief Renvoie l'attenuation constante de Light
  *
  * @return constantAttenuation
  */
  float getConstant();

  /**
   * @brief Change l'attenuation constante de Light
   *
   * @param[in] nConstant attenuation constante
   */
  void setConstant(float nConstant);
  
  /**
  * @brief Renvoie l'attenuation linéaire de Light
  *
  * @return linearAttenuation
  */
  float getLinear();

  /**
   * @brief Change l'attenuation linéaire de Light
   *
   * @param[in] nLinear attenuation linéaire
   */
  void setLinear(float nLinear);
  
  /**
  * @brief Renvoie l'attenuation quadratique de Light
  *
  * @return quadraticAttenuation
  */
  float getQuadratic();

  /**
   * @brief Change l'attenuation quadratique de Light
   *
   * @param[in] nQuadratic attenuation quadratique
   */
  void setQuadratic(float nQuadratic);

private:
  Vector2f pos; //<! postion de Light
  Vector3i RGB; //<! Couleur de la lumière
  float intensity; //<! Intensité de la lumière
  float constantAttenuation; //<! Attnuation constante
  float linearAttenuation; //<! Attnuation linéaire
  float quadraticAttenuation; //<! Attnuation quadratique
};

#endif // ! LIGHT_CLASS_H

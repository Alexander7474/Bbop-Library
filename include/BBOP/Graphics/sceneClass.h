#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <variant>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "cameraClass.h"
#include "bbopMathClass.h"
#include "spriteClass.h"
#include "shaderClass.h"
#include "shaders.h"
#include "bbopGlobal.h"
#include "lightClass.h"

struct UniformLight {
  glm::vec2 pos; // Position de la source de lumière (2D)
  float p0[2];
  glm::vec3 color; // Couleur de la lumière
  float intensity; // Intensité de la lumière
  float constantAttenuation; // Attnuation constante
  float linearAttenuation; // Attnuation linéaire
  float quadraticAttenuation; // Attnuation quadratique
  float p1[1];
};

/**
 * @class Scene
 * @brief Gère la scene et affiche des BbopDrawable
 * @details Tous les paramètre d'affichage sont gèré par Scene comme la lumières ambiante, la camera ou encore les points de lumièrenderModeLoc. La Scene gère donc l'environement de vos BbopDrawable
 * @details La class Scene gère les shaders d'affichage
 * @see BbopDrawable
 *
 * @attention Cette class est obligatoire pour afficher des éléments
 * @todo Ajouter la possibilité de créer des shader personnalisé et de gérer des normal maps
 */
class Scene
{
public:

  /**
  * @brief Constructeur par défault de Scene 
  * @details La scene par défault est éclairé par une lumière blanche d'intensité 1.0
  */
  Scene();

  /**
  * @brief Constructeur de Scene 
  *
  * @param[in] nAmbiantLightValue Intensité de la lumière ambiante 
  * @param[in] nAmbiantLightColor Couleur de la lumière ambiante
  */
  Scene(float nAmbiantLightValue, Vector3i nAmbiantLightColor);
  ~Scene();

  /**
  * @brief Charge les valeur de la scene dans le shader de celle ci 
  *
  * @param[in] window Fenêtre GLFW utilisée par votre programme et initialisée avec bbopInit()
  *
  * @attention Cette méthode est à utiliser à l'initialisation de votre programme et avant chaque changement de scene si la scene doit changer
  */
  void Use(GLFWwindow*& window);

  /**
  * @brief Utilise une camera pour Draw avec la scene 
  *
  * @param[in] camAddr Addresse de la camera à utiliser ou pointeur ves celle ci, nullptr pour la cam par défault
  *
  * @attention Cette méthode utilise le prisme de la camera passé en paramètre pour tous les prochains Draw(), pour revenir à la camera par défault il faut l'utilser avec nullptr comme camAddr
  */
  void useCamera(Camera *camAddr);

  /**
   * @brief Change l'intensité de la lumière ambiante de Scene
   * @see Camera
   *
   * @param[in] nAmbiantLightValue Intensité
   */
  void setAmbiantLightValue(float nAmbiantLightValue);

  /**
   * @brief Renvoie l'intensité de la lumière ambiante de Scene
   *
   * @return ambiantLightValue Intensité de la lumière ambiante
   */
  float getAmbiantLightValue() const;

  /**
   * @brief Change la couleur de la lumière ambiante de Scene
   *
   * @param[in] nAmbiantLightColor Couleur de la lumière ambiante
   */
  void setAmbiantLightColor(const Vector3i &nAmbiantLightColor);

  /**
   * @brief Renvoie la couleur de la lumière ambiante de Scene
   *
   * @return ambiantLightColor Couleur de la lumière ambiante
   */
  const Vector3i &getAmbiantLightColor() const;

  /**
  * @brief Ajoute un point de lumière dans la Scene
  * @see Light
  *
  * @param[in] l point de lumière
  *
  * @attention La list de Light de Scene est reset à chaque usage de Use(), il est donc nécessaire d'ajouter vos point de lumière avant de spécifier la scene à utilser dans votre rendue de frame 
  */
  void addLight(Light& l);

  /**
  * @brief Permet de dessiner sur la fenêtre GFLW initialisée dans bbopInt() avec l'environement de la Scene
  *
  * @param[in] spr Objet à dessiner
  */
  void Draw(const BbopDrawable& spr)const;

private:
  Shader sceneShader; //<! shader 
  float ambiantLightValue; //<! intensité lumière ambiante
  Vector3i ambiantLightColor; //<! couleur lumière ambiante
  GLint ambiantLightLoc; //<! GPU MEM addr de la lumière ambiante
  GLint renderModeLoc; //<! GPU MEM addr du mode de renue (BBOP_SHADER_MODE_COLOR, BBOP_SHADER_MODE_TEXTURE, BBOP_SHADER_MODE_MIX)
  GLint windowSizeLoc; //<! GPU MEM addr de la taille en pixel de l'écran 
  GLint windowResoLoc; //<! GPU MEM addr de la resolution d'affichage de bbop
  GLint nLightLoc; //<! GPU MEM addr de la list de lumière dans le shader
  GLuint lightsUBO; //<! ID de l'ubo pour transfert la list de UniformLight vers la list de Light ddu shader
  std::vector<UniformLight> lightsVec; //<! Liste des lumières à transférer vers le shader avec lightUBO
  Vector3f ambiantLight; //<! lumière ambiante de Scene
  Camera* sceneCamera; //<! camera à utilser lors de Draw()
};

#endif // !SCENE_CLASS_H

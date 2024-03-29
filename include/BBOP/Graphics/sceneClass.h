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
 * @details Tous les paramètre d'affichage sont gèré par Scene comme la lumières ambiante, la camera ou encore les points de lumière.
 *
 * @attention Cette class est obligatoire pour afficher des éléments
 */
class Scene
{
public:
  Scene();
  Scene(float nAmbiantLightValue, Vector3i nAmbiantLightColor);
  ~Scene();

  void Use(GLFWwindow*& window);
  void useCamera(Camera *camAddr);
  void setAmbiantLightValue(float nAmbiantLightValue);
  float getAmbiantLightValue();
  void setAmbiantLightColor(Vector3i nAmbiantLightColor);
  Vector3i getAmbiantLightColor();
  void addLight(Light& l);
  void Draw(BbopDrawable& spr);
private:
  Shader sceneShader;
  float ambiantLightValue;
  Vector3i ambiantLightColor;
  GLint ambiantLightLoc;
  GLint renderModeLoc;
  GLint windowSizeLoc;
  GLint windowResoLoc;
  GLint nLightLoc;
  GLuint lightsUBO;
  std::vector<UniformLight> lightsVec;
  Vector3f ambiantLight;
  Camera* sceneCamera;
};

#endif // !SCENE_CLASS_H

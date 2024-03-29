#ifndef GLOBALS_H
#define GLOBALS_H

/**
 * Local headers
 */
#include "bbopMathClass.h"

/**
 * External headers
 */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
#include <fstream>

/**
 * @brief RenderMode avec uniquement les textures
 */
extern int BBOP_SHADER_MODE_TEXTURE;

/**
 * @brief RenderMode avec uniquement les couleurs
 */
extern int BBOP_SHADER_MODE_COLOR;

/**
 * @brief RenderMode en mixant les textures et les couleurs
 */
extern int BBOP_SHADER_MODE_MIX;

/**
 * @brief Variable global qui stoke la résolution de la fenêtre.
 * @details Pour récupérer la taille réel de la fenêtre (si elle est redimenstionné après sa création) il faut utiliser glfwGetWindowSize().
 */
extern Vector2i BBOP_WINDOW_SIZE;

/**
 * @brief Récupère les données d'un fichier et les renvoie sous forme de string.
 * @details Cette fonction est seulement utilisé par la class Shader.
 * 
 * @param[in] filename Chemin d'accès vers le fichier à lire.
 * @return std::string Contenu du fichier.
 *
 * @see Shader
 * @todo Changer son nom en bbopGetFileData et la déplacer dans bbopFunc.h et bbopFunc.cpp
 */
std::string getFileData(const char* filename);

/**
 * @class BbopDrawable
 * @brief Class Parent de tous ce qui peut être dessiné par une Scene.
 * @details La class Scene utilise cette comme paramètre dans Draw(BbopDrawable).
 *
 * @see Scene
 */
class BbopDrawable
{
public:

  /**
   * @brief Déssine l'objet héritant de la class.
   * @details Cette méthode est utilisé dans Scene.Draw(BbopDrawable) qui lui transmet le renderModeLoc.
   *
   * @see Scene.Draw(BbopDrawable)
   */
  virtual void Draw(GLint renderModeLoc) const = 0;

};

#endif // ! GLOBALS_H

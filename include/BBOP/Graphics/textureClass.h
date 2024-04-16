/*
 * textureClass.h
 *
 * Ce programme est distribué sous les termes de la Licence Publique
 * Générale GNU, version 3.0, telle que publiée par la Free Software
 * Foundation. Consultez la Licence Publique Générale GNU pour plus de
 * détails.
 *
 * Vous devez avoir reçu une copie de la Licence Publique Générale GNU
 * en même temps que ce programme. Si ce n'est pas le cas, consultez
 * <https://www.gnu.org/licenses/>.
 */

#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "bbopMathClass.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

/**
 * @class Texture
 * @brief Contient une texture qui peut être utilisé dans un sprite
 * 
 * @attention La class texture à été testé uniqument sur des images png 
 * @see Sprite 
 *
 * @todo Ajouter la possibilité de gérer plusieur format d'image comme jpg, jpeg, ou gif ext...
 * @todo Ajouter la possibilité de généré un list de Texture a partir d'une sprite sheet avec le nombre de colonnes et de lignes
 */
class Texture 
{
public:

  /**
  * @brief Constructeur par défault de la class Texture 
  *
  * @param[in] textureFileName Chemin d'accès vers la texture
  *
  * @attention Uniquement des fichier png 
  */
  Texture(const char* textureFileName);
  
  /**
  * @brief Permet de bin la texture a opengl avant de Draw
  *
  * @note A utiliser en général avec NoTextureSprite
  *
  * @see NoTextureSprite
  */
  void Bind() const;

  /**
  * @brief Détache la texture d'opengl
  */
  void Unbind() const;

  /**
  * @brief Supprime la texture d'opengl
  */
  void Delete();

  /**
  * @brief Renvoie la larguer de la Texture 
  *
  * @return width largeur
  */
  int getWidth() const;

  /**
  * @brief Renvoie la hauteur de la Texture 
  *
  * @return height hauteur
  */
  int getHeight() const;
private:
  GLuint ID; //<! ID de la texture avec opengl
  int width, height, nrChannels; //<! info sur la texture 
};

#endif // !TEXTURE_CLASS_H

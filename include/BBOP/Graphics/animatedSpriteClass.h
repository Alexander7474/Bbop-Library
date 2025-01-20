#pragma once 

#include <string>
#include <vector>

#include "spriteClass.h"

/**
 * @class AnimatedSprite
 * @brief Gère un Sprite qui joue une aniomation en boucle 
 *
 * @todo Ajouter une class StateSprite qui gère un sprite et qui l'anime en fonction d'une énumération d'état de ce Sprite
 */
class AnimatedSprite : public Sprite
{
public: 
  AnimatedSprite();
  AnimatedSprite(std::string _animated_sprite_sheet, Vector2i _size, float _frame_t);
  AnimatedSprite(std::string _animated_sprite_sheet, Vector2i _size, float _frame_t, int _dead_frame);

  /**
  * @brief Met a jour les particules 
  *
  * @return bool renvoie true si l'animation est fini
  */
  bool update();

  /**
  * @brief renvoie la liste de texture 
  */
  std::vector<Texture>& getSpriteSheet();
private:
  std::vector<Texture> animated_sprite_texture; 
  long unsigned int frame_cpt; //<! compteur de frame
  long unsigned int n_frame; //<! nombre de frame 
  float frame_t; //<! timing entre les frames
  float total_t; //<! temps total de l'anim
  float anim_start; //<! depart de l'anim 
  float last_frame_t; //<! timing de la dernière frame
};

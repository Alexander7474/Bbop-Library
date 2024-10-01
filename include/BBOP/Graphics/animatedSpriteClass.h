#pragma once 

#include <string>
#include <vector>

#include "spriteClass.h"

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
private:
  std::vector<Texture> animated_sprite_texture; 
  long unsigned int frame_cpt; //<! compteur de frame
  long unsigned int n_frame; //<! nombre de frame 
  float frame_t; //<! timing entre les frames
  float total_t; //<! temps total de l'anim
  float anim_start; //<! depart de l'anim 
  float last_frame_t; //<! timing de la dernière frame
};

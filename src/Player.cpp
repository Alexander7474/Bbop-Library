#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

#include "../include/Player.h"

Player::Player(const string name,const string spritePath)
: playerName(name),
  playerSpriteTexturePath(spritePath)
  {
    sf::Texture playerSpriteTexture;
    if (!playerSpriteTexture.loadFromFile(playerSpriteTexturePath)){
        cout << "ERREUR: problème lors du chargement de l'Texture de '" << playerName << "'" << endl; 
    }
    playerSprite.setTexture(playerSpriteTexture);
    cout << "sa marche " << playerSpriteTexturePath << playerName << endl; 
}
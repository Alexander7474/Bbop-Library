#ifndef PLAYER_H  
#define PLAYER_H

#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Player {
public:
    Player(const string name = "DefaultPlayerName",const string spritePath = "imgTesting/noTexture.png");
    string playerName;
    sf::Sprite playerSprite;

private:
    string playerSpriteTexturePath;
};

#endif  // PLAYER_H

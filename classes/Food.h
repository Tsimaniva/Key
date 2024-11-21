//
// Created by REVUZ on 10/20/2024.
//

#ifndef BIRD_FOOD_H
#define BIRD_FOOD_H

#include <SFML/Graphics.hpp>
class Food {
public:
Food(float posX, float posY,sf::Texture &texture);
void moveLeft();
sf::Sprite getFood() const;
float getPosX();
float getPosY();
sf::Sprite sprite;
private:
    sf::Sprite foodSprite;
    sf::Texture foodTexture;
    float posX,posY;
    const float speed = 0.4f;
};


#endif //BIRD_FOOD_H

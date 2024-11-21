//
// Created by REVUZ on 10/16/2024.
//

#ifndef BIRD_BIRD_H
#define BIRD_BIRD_H
#include <SFML/Graphics.hpp>

class Bird {
public: Bird();
    void update();
    void reset();
    sf::Sprite getSprite() const;
    bool isOffScreen(float screenHeight);
    void setHungry(bool isHungry);
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float velocityY;
    bool isHungry;
    float gravity;
};


#endif //BIRD_BIRD_H

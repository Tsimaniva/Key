//
// Created by REVUZ on 10/16/2024.
//

#include "Bird.h"
Bird::Bird(){
    if(texture.loadFromFile("../img/bird.png")){

    }
    isHungry = false;
    gravity =  0.0008f;
    sprite.setTexture(texture);
    sprite.setPosition(100,300);
    sprite.setScale(0.08f,0.08f);
    velocityY = 0;
}
void Bird :: setHungry(bool isHungry){
    this->isHungry = isHungry;
}
void Bird :: update(){
    velocityY += gravity;
    sprite.move(0,velocityY);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        if(!this->isHungry)
        velocityY = -0.2;
        else
        {velocityY = -0.05;
            gravity = 0.001f;

        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        this->sprite.setPosition(this->sprite.getPosition().x + 0.1, this->sprite.getPosition().y);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        this->sprite.setPosition(this->sprite.getPosition().x - 0.2, this->sprite.getPosition().y);
    }
}
void Bird :: reset(){
    sprite.setPosition(100,300);
    velocityY = 0;
}
bool Bird::isOffScreen(float screenHeight) {
    return sprite.getPosition().y > screenHeight || sprite.getPosition().y < 0;
}
sf::Sprite Bird :: getSprite() const {
    return sprite;
}

//
// Created by REVUZ on 10/20/2024.
//

#include "Food.h"
#include<iostream>
#include <SFML/Graphics.hpp>

Food::Food(float posX, float posY,sf::Texture &texture){

    if(!foodTexture.loadFromFile("../img/Sans titre 6_20241020143119.png")){
        std::cout<<"tsy poinsa"<<std::endl;
    }
    foodSprite.setTexture(foodTexture);

    sprite.setTexture(foodTexture);
    sprite.setPosition(posX,posY);
    sprite.setScale(0.05,0.05);

    foodSprite.setPosition(posX,posY);
}
void Food:: moveLeft(){
    sprite.move(-speed,0.f);
}
sf::Sprite Food::getFood() const{
    return foodSprite;
}
float Food ::getPosX() {
    return posX;
}
float Food ::getPosY() {
    return posY;
}
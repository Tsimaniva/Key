//
// Created by REVUZ on 10/16/2024.
//

#include "Pipe.h"
#include <cstdlib>
#include <iostream>
#include<SFML/Graphics.hpp>
#include<cstdlib>
#include<ctime>
Pipe::Pipe(float startX){
    texture.loadFromFile("../img/Airship-PNG-File1.png");
    texture1.loadFromFile("../img/Airship-PNG-Image.png");
    texture2.loadFromFile("../img/colorful-hot-air-balloon-in-clear-blue-sky-free-png.png");
    airShip.setTexture(texture);
    airShip1.setTexture(texture1);
    hotAirBalloon.setTexture(texture2);
    actualSprite = getRandomSprite();

    airShip.setScale(0.5,0.5);
    hotAirBalloon.setScale(0.3,0.3);
    airShip1.setScale(0.5,0.5);

    reset(startX);
}
sf::Sprite& Pipe:: getRandomSprite(){
    int randomValue = rand()% 3;
    if(randomValue == 0){
        return airShip;
    }
    else if(randomValue == 1){
        return airShip1;
    }
    else{
        return hotAirBalloon;
    }
}

void Pipe::update() {
    actualSprite.move(-pipeSpeed, 0);
//    bottomPipe.move(-pipeSpeed,0);//topPipe.getGlobalBounds().width
    if(actualSprite.getPosition().x < -1250){
        reset(1250);
    }
}
void Pipe::reset(float startX){
    float pipeY = rand() % 400 + 100;
    actualSprite = getRandomSprite();
    actualSprite.setPosition(startX,pipeY);
//    bottomPipe.setPosition(startX,pipeY + gapSize);
}
sf::Sprite Pipe ::getActualPipe()const {
    return actualSprite;
}
//sf::Sprite Pipe::getBottomPipe() const {
//    return bottomPipe;
//}
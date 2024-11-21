//
// Created by REVUZ on 10/16/2024.
//

#ifndef BIRD_PIPE_H
#define BIRD_PIPE_H
#include <SFML/Graphics.hpp>

class Pipe {
public:
    Pipe(float startX);
    void update();
    void reset(float startX);
    sf::Sprite getActualPipe() const;
    sf::Sprite getBottomPipe() const;
    sf::Sprite& getRandomSprite();
private:
    sf::Texture texture, texture1, texture2;
    sf::Sprite airShip, airShip1, hotAirBalloon;

    sf::Sprite actualSprite;
    const float pipeSpeed = 0.5f;
};


#endif //BIRD_PIPE_H

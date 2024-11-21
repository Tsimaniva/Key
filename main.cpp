#include <iostream>
#include<SFML/Graphics.hpp>
#include "classes/Bird.h"
#include "classes/Pipe.h"
#include "classes/Food.h"
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <vector>
#include <sstream>
#include <fstream>

using namespace sf;
using namespace std;


//conversion du couleur hexa en RGBA

sf::Color hexToColor(const std::string& hexCode) {
    unsigned int red, green, blue, alpha = 255; // Alpha par défaut à 255 (opaque)

    // Vérifie si le code commence par '#'
    if (hexCode[0] == '#') {
        std::stringstream ss;
        if (hexCode.size() == 7) { // #RRGGBB
            ss << std::hex << hexCode.substr(1, 2); // RR
            ss >> red;
            ss.clear();
            ss << std::hex << hexCode.substr(3, 2); // GG
            ss >> green;
            ss.clear();
            ss << std::hex << hexCode.substr(5, 2); // BB
            ss >> blue;
        } else if (hexCode.size() == 9) { // #RRGGBBAA
            ss << std::hex << hexCode.substr(1, 2); // RR
            ss >> red;
            ss.clear();
            ss << std::hex << hexCode.substr(3, 2); // GG
            ss >> green;
            ss.clear();
            ss << std::hex << hexCode.substr(5, 2); // BB
            ss >> blue;
            ss.clear();
            ss << std::hex << hexCode.substr(7, 2); // AA
            ss >> alpha;
        }
        return sf::Color(red, green, blue, alpha);
    } else {
        // Retourne une couleur par défaut en cas de format incorrect
        return sf::Color::Black;
    }
}


//verification du collision entre l'oiseau et les obstacles;

bool checkCollision(const Bird &bird, Sprite actualPipe){
    sf::FloatRect birdBounds = bird.getSprite().getGlobalBounds();
    sf::FloatRect PipeBounds = actualPipe.getGlobalBounds();
//    sf::FloatRect bottomPipeBounds = pipe.getBottomPipe().getGlobalBounds();
    if(birdBounds.intersects(PipeBounds) ){
        return true;
    }
    return false;
}
bool checkFoodCollision(const Bird &bird, const Food &food){
    sf::FloatRect birdBounds = bird.getSprite().getGlobalBounds();
    sf::FloatRect foodBounds = food.sprite.getGlobalBounds();
    if(birdBounds.intersects(foodBounds) ){
        return true;
    }
    return false;
}

int main() {
//    RenderWindow window(VideoMode(800,600),"Bird");
//    Texture backgroundTexture;
//    if(!backgroundTexture.loadFromFile("../img/sunset-header.jpg")){
//        cout<<"image introuvable"<<endl;
//        return -1;
//    }
//    Sprite backgroundSprite;
//    backgroundSprite.setTexture(backgroundTexture);
//    //redemissioner l'arrière plan suivant la fenêtre principale
//    //------------------------
//    Vector2u windowSize = window.getSize();
//    Vector2u textureSize = backgroundTexture.getSize();
//    float scaleX = static_cast<float>(windowSize.x)/textureSize.x;
//    float scaleY = static_cast<float>(windowSize.y)/textureSize.y;
//    backgroundSprite.setScale(scaleX,scaleY);
//    //-------------------------
//    Texture birdTexture;
//    if(!birdTexture.loadFromFile("../img/bird.png"))
//        return - 1;
//    Sprite bird;
//    bird.setTexture(birdTexture);
//    bird.setScale(0.2f,0.2f);
//    bird.setPosition(windowSize.x/2 - birdTexture.getSize().x/2,
//                     windowSize.y/2 - birdTexture.getSize().y/2);
//    while(window.isOpen()){
//        Event event;
//        while(window.pollEvent(event)){
//            if(event.type == Event::Closed)
//                window.close();
//        }
//        window.clear();
//        window.draw(backgroundSprite);
//        window.draw(bird);
//        window.display();
//    }

sf::RenderWindow window(sf::VideoMode(1250,800),"Flappy Bird");
Bird bird;
Pipe pipe(1250);
    Texture backgroundTexture;
    if(!backgroundTexture.loadFromFile("../img/Sans titre 5_20241020091955.png")){
        cout<<"image introuvable"<<endl;
        return -1;
    }
    Sprite backgroundSprite;
    Sprite backgroundSprite1;
      Vector2u windowSize = window.getSize();
      Vector2u textureSize = backgroundTexture.getSize();
      float scaleX = static_cast<float>(windowSize.x)/textureSize.x;
      float scaleY = static_cast<float>(windowSize.y)/textureSize.y;
      //backgroundSprite
      backgroundSprite.setScale(scaleX,scaleY);
      backgroundSprite.setTexture(backgroundTexture);
      //backgroundSprite1
      backgroundSprite1.setScale(scaleX,scaleY);
      backgroundSprite1.setTexture(backgroundTexture);
      //positionnement du deuxieme sprite juste `a coté du premier
      backgroundSprite1.setPosition(backgroundTexture.getSize().x+480,0);
      float speed = 100.0f; //vitesse
      Clock clock;
      Clock clock1;
      float spawnTime = 0.f;

      //Initialiser le generateur de nombres aléatoires
      srand(static_cast<unsigned int>(time(0)));

      vector<Food> foods;
//      Texture foodTexture;
//      foodTexture.loadFromFile("../img/Sans titre 6_20241020143119.png");
//      Sprite foodSprite(foodTexture);
//
//     foodSprite.setPosition(1200, rand() % window.getSize().y);
//
//      foodSprite.setScale(0.05,0.05);
    Texture texture1;
    if(!texture1.loadFromFile("../img/Sans titre 6_20241020143119.png")){
        std::cout<<"tsy poinsa"<<std::endl;
    }
    Sprite t(texture1);

    //Création de pourcentage de calorie
    RectangleShape calorie (Vector2f (300,35));

    calorie.setPosition(850,20);
    Clock clockCalorie;
    float decreaseInterval = 0.008f;
    float lastDecreaseTime = 0;
    calorie.setFillColor(Color::Green);
    float durationCalorie = 30.0f;

    //Creation de cadre
    RectangleShape cadre (Vector2f (300,35));
    cadre.setFillColor(Color::Transparent);
    cadre.setPosition(850,20);
    cadre.setOutlineThickness(2);
    cadre.setOutlineColor(Color::Black);

   //texte du pourcentage de calorie;
   Text text;
   text.setFillColor(Color::White);
   Font font;
   font.loadFromFile("../font/Rockwell.ttf");
   text.setFont(font);

   text.setPosition(985,22);

   Texture birdImage;
   birdImage.loadFromFile("../img/Sans titre 6_20241020143119.png");
   Sprite birdImg(birdImage);
   birdImg.setScale(0.07f,0.07f);
   birdImg.setPosition(1160,20);

   //score
   Text score, bestScore;
   score.setFont(font);
   bestScore.setFont(font);
   score.setPosition(50,50);
    bestScore.setPosition(50,15);
   score.setString("Score actuel : 0 m");
   score.setScale(0.8f,0.8f);
   bestScore.setScale(0.8f,0.8f);

   int valScore;
   int scoreValue;
   ifstream scoreFileEntree("../fichier/bestScore.txt");

   if(scoreFileEntree.is_open()){
       scoreFileEntree >> scoreValue;
       scoreFileEntree.close();
   }
   bestScore.setString("Meilleur score : "+ to_string(scoreValue) + " m");

   // le gameOver
   bool gameOver;
   RectangleShape gameOverMenu;
   gameOverMenu.setSize(Vector2f (1500,800));
  // gameOverMenu.setFillColor(Color(0,0,0,128));
    gameOverMenu.setFillColor(Color::Black);
   Text stat, titreGameOver,restart;
   stat.setFont(font);
   titreGameOver.setFont(font);
   titreGameOver.setString("Game over !");
   titreGameOver.setScale(1.8f,1.8f);
   restart.setFont(font);
   restart.setString("Appuyer sur << ENTRER >> pour rejouer");

   titreGameOver.setPosition(500,280);
   titreGameOver.setFillColor(hexToColor("#FF8D46"));
   stat.setPosition(420,380);
   restart.setPosition(383,440);

while(window.isOpen()){
    sf::Event event;
    ofstream scoreFileSortie("../fichier/bestScore.txt");
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed)
        {


            window.close();
        }
    }
    if(!gameOver) {
        bird.update();
        pipe.update();
        //temps écoulé pour rendre le mouvement fluide
        float deltaTime = clock.restart().asSeconds();
        float deltaTimeFood = clock1.getElapsedTime().asSeconds();
        //deplacement de deux fond vers la gauche
        backgroundSprite.move(-speed * deltaTime, 0);
        backgroundSprite1.move(-speed * deltaTime, 0);

//    foodSprite.move(-speed *deltaTime, 0);
//

        if (deltaTimeFood > spawnTime) {
            float posY = static_cast<float>(rand() % (1200 - 50));
            Food f(1200, posY, texture1);
            foods.push_back(f);//Food(1200,posY,texture1));

            spawnTime = static_cast<float>((rand() % 2000 + 1000) / 1000.f);
            clock1.restart();

        }


        for (auto &food: foods) {
            food.moveLeft();
            if (checkFoodCollision(bird, food)) {
                food.sprite.setPosition(-150, -1503);

                float newSize = calorie.getSize().x + 30;
                if (newSize > 300) {
                    calorie.setSize(Vector2f(300, 35));
                } else { calorie.setSize(Vector2f(newSize, 35)); }
            }
        }
//        Sprite food(foodTexture);
//        food.setPosition(1200, rand() % window.getSize().y);


        if (backgroundSprite.getPosition().x <= -1240) {
            backgroundSprite.setPosition(1240, 0);
        }
        if (backgroundSprite1.getPosition().x <= -1240) {
            backgroundSprite1.setPosition(1240, 0);
        }


//    backgroundSprite.move(-0.1f,0);
        if (bird.isOffScreen(800) || checkCollision(bird, pipe.getActualPipe())) {
//            bird.reset();
//            pipe.reset(1000);
            gameOver = true;
        }

        // Calcul de temps écoulé
        float elapsed1 = clockCalorie.getElapsedTime().asSeconds();
//    if(elapsed1 < durationCalorie){
//        float newHeight = 300 * (1 - elapsed1 / durationCalorie) ;
//        calorie.setSize(Vector2f(newHeight,35));
//    }
        if (elapsed1 - lastDecreaseTime >= decreaseInterval) {
            float newWidth = calorie.getSize().x - 0.1;
            if (newWidth > 0) {
                calorie.setSize(Vector2f(newWidth, 35));
                lastDecreaseTime = elapsed1;
                float pourcentage;
                pourcentage = (newWidth * 100) / 300;
                text.setString(to_string(static_cast<int> (pourcentage)) + "%");
            }

        }
        valScore++;
        if (valScore % 100 == 0) {
            score.setString("Score actuel : " + to_string(valScore / 100) + " m");
        }
        if (calorie.getSize().x < 50) {
            bird.setHungry(true);
            calorie.setFillColor(hexToColor("#FF5733"));
        } else {
            bird.setHungry(false);
            calorie.setFillColor(hexToColor("#3EC247"));
        }
        window.clear();
    }

    window.draw(backgroundSprite);
    window.draw(backgroundSprite1);
    window.draw(bird.getSprite());
    window.draw(pipe.getActualPipe());
    for(auto& food:foods){
        food.sprite.setTexture(texture1);
        window.draw(food.sprite);
    }
    window.draw(calorie);
    window.draw(cadre);
    window.draw(text);
    window.draw(birdImg);
    window.draw(score);
    window.draw(bestScore);
//    window.draw(pipe.getBottomPipe());
    if(gameOver){
        if(scoreValue < (valScore/100)){
            if(scoreFileSortie.is_open()){
                scoreFileSortie << to_string(valScore/100);
            }
        }
        else{
            scoreFileSortie << scoreValue;
        }

        scoreFileSortie.close();
        stat.setString("Vous avez obtenu le score de : "+ to_string(valScore/100) + " m");
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            bird.reset();
            pipe.reset(1000);
            gameOver = false;
            valScore = 0;
        }
        window.draw(gameOverMenu);
        window.draw(titreGameOver);
        window.draw(stat);
        window.draw(restart);

    }
    window.display();




}

    return 0;
}

//
// Created by pc on 06.07.2026.
//

#ifndef FRUIT_HPP
#define FRUIT_HPP
#include <random>
#include "SFML/Graphics/RectangleShape.hpp"

enum fruits{BALL, BONE, SOCK};

class Fruit {

    public:
    Fruit() {
        randomize();
        ballTexture.loadFromFile("../assets/textures/fruit/ball.png");
        boneTexture.loadFromFile("../assets/textures/fruit/bone.png");
        sockTexture.loadFromFile("../assets/textures/fruit/sock.png");
    }

    void draw(sf::RenderWindow &window) {

        sf::Sprite sprite;
        if (currentFruit == BALL) {
            sprite.setTexture(ballTexture);
        } else if (currentFruit == BONE) {
            sprite.setTexture(boneTexture);
        } else if (currentFruit == SOCK) {
            sprite.setTexture(sockTexture);
        }

        float x = position.x * 40.f + 25.f;
        float y = position.y * 40.f + 125.f;

        sprite.setPosition(x, y);
        window.draw(sprite);
    }

    void randomize() {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> distr(0, 14);
        position.x = distr(gen);
        position.y = distr(gen);

        std::uniform_int_distribution<> fruitDistr(0, 2);
        currentFruit = static_cast<fruits>(fruitDistr(gen));
    }

    sf::Vector2i getPosition(){
        return position;
    }

private:
    sf::Vector2i position;
    sf::Texture ballTexture;
    sf::Texture boneTexture;
    sf::Texture sockTexture;
    fruits currentFruit;
};



#endif //FRUIT_HPP

//
// Created by pc on 06.07.2026.
//

#ifndef FRUIT_HPP
#define FRUIT_HPP
#include <random>
#include "SFML/Graphics/RectangleShape.hpp"

class Fruit {

    public:
    Fruit() {
        randomize();
    }

    void draw(sf::RenderWindow &window) {
        sf::RectangleShape owoc(sf::Vector2f(40.f,40.f));
        sf::Color czerwo(200, 0, 0);
        owoc.setFillColor(czerwo);
        float x = position.x * 40 + 50;
        float y = position.y * 40 + 150;
        owoc.setPosition(sf::Vector2f(x,y));
        window.draw(owoc);
    }

    void randomize() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, 14);
        position.x = distr(gen);
        position.y = distr(gen);
    }

    sf::Vector2i getPosition(){
        return position;
    }

private:
    sf::Vector2i position;
};



#endif //FRUIT_HPP

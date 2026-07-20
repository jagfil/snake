//
// Created by pc on 20.07.2026.
//
#ifndef GAME_HPP
#define GAME_HPP

#include "Snake.hpp"
#include "Fruit.hpp"
#include <SFML/Graphics.hpp>

enum State { MENU, PLAYING, GAMEOVER };

class Game {
public:

    Game() : window (sf::VideoMode(700,800),"Snake") {
        window.setFramerateLimit(60);
    }

    bool isRunning() {
        return window.isOpen();
    }

    void update() {
        if (clock.getElapsedTime().asSeconds() >= 0.13f) {
            clock.restart();
            snake.move();
            if (snake.getHeadPosition() == fruit.getPosition()) {
                snake.growth();
                do {
                    fruit.randomize();
                } while (snake.amIHere(fruit.getPosition()));
            }
            snake.collision();
            if (snake.isDead()) {
                //game over
            }
        }
    }

    void draw() {
        window.clear(sf::Color(149, 141, 252));

        for (int i = 0; i <= 14; i++) {
            for (int j = 0; j <= 14; j++) {
                if ((i+j)%2 == 0 ) {
                    kafel.setFillColor(rozowyciem);
                }else {
                    kafel.setFillColor(rozowyjas);
                }
                pixelX = j * 40 + 50;
                pixelY = i * 40 + 150;
                kafel.setPosition(sf::Vector2f(pixelX, pixelY));
                window.draw(kafel);
            }
        }
        snake.draw(window);
        fruit.draw(window);
        window.display();
    }

    void input() {
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::W) {
                    snake.changeDirection(UP);

                } else if (event.key.code == sf::Keyboard::S) {
                    snake.changeDirection(DOWN);

                } else if (event.key.code == sf::Keyboard::A) {
                    snake.changeDirection(LEFT);

                } else if (event.key.code == sf::Keyboard::D) {
                    snake.changeDirection(RIGHT);
                }
            }
        }
    }

private:
    Snake snake;
    Fruit fruit;
    State state = PLAYING;
    sf::Clock clock;
    sf::RenderWindow window;
    sf::Event event;
    sf::Color rozowyciem = sf::Color(255, 204, 253);
    sf::Color rozowyjas = sf::Color (255, 183, 232);
    sf::RectangleShape kafel = sf::RectangleShape(sf::Vector2f(40.f,40.f));
    float pixelX;
    float pixelY;
};



#endif //GAME_HPP

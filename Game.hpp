//
// Created by pc on 20.07.2026.
//
#ifndef GAME_HPP
#define GAME_HPP

#include "Snake.hpp"
#include "Fruit.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

enum State { MENU, PLAYING, STARTING };

class Game {
public:

    Game() : window (sf::VideoMode(650,750),"Snake") {
        window.setFramerateLimit(60);
        font.loadFromFile("assets/fonts/CatMeow-Regular.ttf");
    }

    bool isRunning() {
        return window.isOpen();
    }

    void update() {
        if (state == PLAYING) {
            if (clock.getElapsedTime().asSeconds() >= 0.13f) {
                clock.restart();
                snake.move();
                if (snake.getHeadPosition() == fruit.getPosition()) {
                    snake.growth();
                    score++;
                    do {
                        fruit.randomize();
                    } while (snake.amIHere(fruit.getPosition()));
                }
                snake.collision();
                if (snake.isDead()) {
                    state = MENU;
                }
            }
        }
    }

    void draw() {
        window.clear(sf::Color(252, 167, 219));
        frame.setFillColor(sf::Color(240, 151, 193));
        window.draw(frame);
        for (int i = 0; i <= 14; i++) {
            for (int j = 0; j <= 14; j++) {
                if ((i+j)%2 == 0 ) {
                    chunk.setFillColor(rozowyciem);
                }else {
                    chunk.setFillColor(rozowyjas);
                }
                pixelX = j * 40 + 25;
                pixelY = i * 40 + 125;
                chunk.setPosition(sf::Vector2f(pixelX, pixelY));
                window.draw(chunk);
            }
        }
        snake.draw(window);
        fruit.draw(window);

        scoreText.setFont(font);
        scoreText.setCharacterSize(40);
        scoreText.setString(std::string("Score: ") + std::to_string(score));
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(25, 25);
        window.draw(scoreText);

        highScoreText.setFont(font);
        highScoreText.setCharacterSize(40);
        highScoreText.setString(std::string("High Score: ") + std::to_string(highScore));
        highScoreText.setFillColor(sf::Color::White);
        highScoreText.setPosition(300, 25);
        window.draw(highScoreText);

        if (state == STARTING) {

        }

        if (state == MENU) {
            menu.setPosition(125, 150);
            menu.setFillColor(sf::Color(171, 97, 134));
            menuBack.setFillColor(sf::Color(0,0,0,180));
            window.draw(menuBack);
            window.draw(menu);
        }

        window.display();
    }

    void input() {
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (state == STARTING){

                    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                        snake.changeDirection(UP);
                        state = PLAYING;

                    } else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
                        snake.changeDirection(DOWN);
                        state = PLAYING;

                    } else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
                        snake.changeDirection(RIGHT);
                        state = PLAYING;
                    }
                }else if (state == PLAYING){

                    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                        snake.changeDirection(UP);

                    } else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
                        snake.changeDirection(DOWN);

                    }else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
                        snake.changeDirection(LEFT);

                    } else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
                        snake.changeDirection(RIGHT);
                    }
                }else if (state == MENU) {
                    if (event.key.code == sf::Keyboard::R ||
                        event.key.code == sf::Keyboard::Enter ||
                        event.key.code == sf::Keyboard::Space) {
                        snake.restart();
                        fruit.randomize();
                        if (score > highScore) {
                            highScore = score;
                        }
                        score = 0;
                        state = STARTING;
                    }
                }
            }
        }
    }

private:
    Snake snake;
    Fruit fruit;
    State state = MENU;
    sf::Clock clock;
    sf::RenderWindow window;
    sf::Event event;
    sf::Color rozowyciem = sf::Color(255, 204, 253);
    sf::Color rozowyjas = sf::Color (255, 183, 232);
    sf::RectangleShape chunk = sf::RectangleShape(sf::Vector2f(40.f,40.f));
    sf::RectangleShape frame = sf::RectangleShape(sf::Vector2f(700.f,100.f));
    sf::RectangleShape menu = sf::RectangleShape(sf::Vector2f(400.f,500.f));
    sf::RectangleShape menuBack = sf::RectangleShape(sf::Vector2f(700.f,750.f));

    float pixelX;
    float pixelY;
    int score = 0;
    int highScore = 0;
    sf::Font font;
    sf::Text scoreText;
    sf::Text highScoreText;
};



#endif //GAME_HPP

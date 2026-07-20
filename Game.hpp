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

enum State { MENU, PLAYING, GAMEOVER };

class Game {
public:

    Game() : window (sf::VideoMode(700,750),"Snake") {
        window.setFramerateLimit(60);
        font.loadFromFile("assets/CatMeow-Regular.ttf");
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
                    state = GAMEOVER;
                }
            }
        }
    }

    void draw() {
        window.clear(sf::Color(252, 167, 219));

        for (int i = 0; i <= 14; i++) {
            for (int j = 0; j <= 14; j++) {
                if ((i+j)%2 == 0 ) {
                    chunk.setFillColor(rozowyciem);
                }else {
                    chunk.setFillColor(rozowyjas);
                }
                pixelX = j * 40 + 50;
                pixelY = i * 40 + 100;
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
        highScoreText.setPosition(350, 25);
        window.draw(highScoreText);

        window.display();
    }

    void input() {
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                //Menu
                if (state == MENU){

                    if (event.key.code == sf::Keyboard::W) {
                        snake.changeDirection(UP);
                        state = PLAYING;

                    } else if (event.key.code == sf::Keyboard::S) {
                        snake.changeDirection(DOWN);
                        state = PLAYING;

                    } else if (event.key.code == sf::Keyboard::D) {
                        snake.changeDirection(RIGHT);
                        state = PLAYING;
                    }
                    //playing
                }else if (state == PLAYING){

                    if (event.key.code == sf::Keyboard::W) {
                        snake.changeDirection(UP);

                    } else if (event.key.code == sf::Keyboard::S) {
                        snake.changeDirection(DOWN);

                    }else if (event.key.code == sf::Keyboard::A) {
                        snake.changeDirection(LEFT);

                    } else if (event.key.code == sf::Keyboard::D) {
                        snake.changeDirection(RIGHT);
                    }
                    //GameOver
                }else if (state == GAMEOVER) {
                    if (event.key.code == sf::Keyboard::R ||
                        event.key.code == sf::Keyboard::Enter ||
                        event.key.code == sf::Keyboard::Space) {
                        snake.restart();
                        fruit.randomize();
                        if (score > highScore) {
                            highScore = score;
                        }
                        score = 0;
                        state = MENU;
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
    float pixelX;
    float pixelY;
    int score = 0;
    int highScore = 0;
    sf::Font font;
    sf::Text scoreText;
    sf::Text highScoreText;
};



#endif //GAME_HPP

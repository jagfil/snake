#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "Fruit.hpp"

int main() {

    sf::RenderWindow window(sf::VideoMode(800,800),"Snake");
    window.setFramerateLimit(600);
    sf::Color rozowyciem (255, 204, 253);
    sf::Color rozowyjas (255, 183, 232);
    sf::Clock clock;
    sf::RectangleShape kafel = sf::RectangleShape(sf::Vector2f(40.f,40.f));
    float pixelX;
    float pixelY;
    Snake snake;
    Fruit fruit;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) {
                    snake.changeDirection(UP);
                } else if (event.key.code == sf::Keyboard::S) {
                    snake.changeDirection(DOWN);
                }else if (event.key.code == sf::Keyboard::A) {
                    snake.changeDirection(LEFT);
                }else if (event.key.code == sf::Keyboard::D) {
                    snake.changeDirection(RIGHT);
                }
            }
        }

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

        window.clear(sf::Color::White);

        for (int i = 0; i <= 19; i++) {
            for (int j = 0; j <= 19; j++) {
                if ((i+j)%2 == 0 ) {
                    kafel.setFillColor(rozowyciem);
                }else {
                    kafel.setFillColor(rozowyjas);
                }
                pixelX = j * 40;
                pixelY = i * 40;
                kafel.setPosition(sf::Vector2f(pixelX, pixelY));
                window.draw(kafel);
            }
        }

        snake.draw(window);
        fruit.draw(window);

        window.display();
    }

    return 0;
}
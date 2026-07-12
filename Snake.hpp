//
// Created by pc on 06.07.2026.
//

#ifndef SNAKE_HPP
#define SNAKE_HPP
#include <vector>
#include "SFML/Graphics/RectangleShape.hpp"

enum Direction { UP, DOWN, LEFT, RIGHT };

class Snake {
public:

    Snake() {
        body.push_back(sf::Vector2i(6, 11));
        body.push_back(sf::Vector2i(5, 11));
        body.push_back(sf::Vector2i(4, 11));
        direction = RIGHT;
    }

    void draw(sf::RenderWindow &window) {
        sf::RectangleShape segment(sf::Vector2f(40.f,40.f));
        sf::Color braz(120, 76, 0);
        segment.setFillColor(braz);

        for (int i = 0; i < body.size(); i++) {
            float pixelX = body[i].x * 40.f;
            float pixelY = body[i].y * 40.f;
            segment.setPosition(sf::Vector2f(pixelX,pixelY));
            window.draw(segment);
        }
    }

    void changeDirection(Direction newDirection) {
        if (newDirection == UP && direction != DOWN) {
            direction = UP;
        }else if (newDirection == DOWN && direction != UP) {
            direction = DOWN;
        }else if (newDirection == LEFT && direction != RIGHT) {
            direction = LEFT;
        }else if (newDirection == RIGHT && direction != LEFT) {
            direction = RIGHT;
        }
    }

    void move(bool eaten) {
        sf::Vector2i newHead = body[0];
        if (direction == UP) {
            newHead.y--;
        }else if (direction == DOWN) {
            newHead.y++;
        }else if (direction == LEFT) {
            newHead.x--;
        }else if (direction == RIGHT) {
            newHead.x++;
        }
        body.insert(body.begin(), newHead);
        if (!eaten) {
            body.pop_back();
        }
    }

    sf::Vector2i getHeadPosition(){
        return body[0];
    }

private:
    std::vector<sf::Vector2i> body;
    Direction direction;
};



#endif //SNAKE_HPP

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
        canTurn = true;
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
        if (canTurn){
            if (newDirection == UP && direction != DOWN) {
                direction = UP;
                canTurn = false;
            }else if (newDirection == DOWN && direction != UP) {
                direction = DOWN;
                canTurn = false;
            }else if (newDirection == LEFT && direction != RIGHT) {
                direction = LEFT;
                canTurn = false;
            }else if (newDirection == RIGHT && direction != LEFT) {
                direction = RIGHT;
                canTurn = false;
            }
        }
    }

    void move() {
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
        tailPosition = body.back();
        body.insert(body.begin(), newHead);
        body.pop_back();
        canTurn = true;
    }

    void growth() {
        body.push_back(tailPosition);
    }

    sf::Vector2i getHeadPosition(){
        return body[0];
    }

private:
    std::vector<sf::Vector2i> body;
    Direction direction;
    bool canTurn;
    sf::Vector2i tailPosition;
};



#endif //SNAKE_HPP

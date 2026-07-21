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
        body.push_back(sf::Vector2i(4, 10));
        body.push_back(sf::Vector2i(3, 10));
        body.push_back(sf::Vector2i(2, 10));
        direction = RIGHT;
        canTurn = true;
        dead = false;
    }

    void restart() {
        body.clear();
        body.push_back(sf::Vector2i(4, 10));
        body.push_back(sf::Vector2i(3, 10));
        body.push_back(sf::Vector2i(2, 10));
        direction = RIGHT;
        canTurn = true;
        dead = false;
    }

    void draw(sf::RenderWindow &window) {
        sf::RectangleShape segment(sf::Vector2f(40.f,40.f));
        sf::Color braz(120, 76, 0);
        segment.setFillColor(braz);

        for (int i = 0; i < body.size(); i++) {
            float pixelX = body[i].x * 40.f + 25.f;
            float pixelY = body[i].y * 40.f + 125.f;
            segment.setPosition(sf::Vector2f(pixelX,pixelY));
            window.draw(segment);
        }
    }

    void changeDirection(Direction newDirection) {
        if (canTurn && !dead) {
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
        if (!isDead()) {
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
            if (newHead.x < 0 || newHead.y < 0 || newHead.x > 14 || newHead.y > 14) {
                dead = true;
            }else{
                tailPosition = body.back();
                body.insert(body.begin(), newHead);
                body.pop_back();
                canTurn = true;
            }
        }
    }

    void collision() {
        //otoczenie
        if (body[0].x < 0 || body[0].y < 0 || body[0].x > 14 || body[0].y > 14) {
            dead = true;
        }
        //wlasne cialo
        for (int i = 1; i < body.size(); i++) {
            if (body[0] == body[i]){
                dead = true;
            }
        }
    }

    bool amIHere(sf::Vector2i position) {
        for (int i = 0; i < body.size(); i++) {
            if (body[i] == position) {
                return true;
            }
        }
        return false;
    }

    bool isDead() {
        return dead;
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
    bool dead;
    sf::Vector2i tailPosition;
};



#endif //SNAKE_HPP

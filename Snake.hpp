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
        headTexture.loadFromFile("../assets/textures/dog/head.png");
        bodyTexture.loadFromFile("../assets/textures/dog/body.png");
        tailTexture.loadFromFile("../assets/textures/dog/tail.png");
        curveTexture.loadFromFile("../assets/textures/dog/curve.png");
    }

    void draw(sf::RenderWindow &window) {
        //sf::RectangleShape segment(sf::Vector2f(40.f,40.f));
        //sf::Color braz(120, 76, 0);
        //segment.setFillColor(braz);

        sf::Sprite sprite;
        for (int i = 0; i < body.size(); i++) {
            sprite.setRotation(0);
            if (i==0) {
                sprite.setTexture(headTexture);
                sprite.setRotation(getHeadRotation());

            }else if (i==body.size()-1) {
                sprite.setTexture(tailTexture);
                sprite.setRotation(getTailRotation());
            }else {
                if (isCurve(i)) {
                    sprite.setTexture(curveTexture);
                    sprite.setRotation(getCurveRotation(i));
                }else {
                    sprite.setTexture(bodyTexture);
                    sprite.setRotation(getBodyRotation(i));
                }
            }

            float pixelX = body[i].x * 40.f + 25.f;
            float pixelY = body[i].y * 40.f + 125.f;

            sprite.setOrigin(20.f, 20.f);
            sprite.setPosition(pixelX + 20.f, pixelY + 20.f);

            window.draw(sprite);
        }

        //for (int i = 0; i < body.size(); i++) {
          //  float pixelX = body[i].x * 40.f + 25.f;
            //float pixelY = body[i].y * 40.f + 125.f;
            //segment.setPosition(sf::Vector2f(pixelX,pixelY));
            //window.draw(segment);
        //}
    }

    float getHeadRotation() {
        if (direction == UP)
            return 0;
        if (direction == DOWN)
            return 180;
        if (direction == LEFT)
            return 270;
        if (direction == RIGHT)
            return 90;

        return 0;
    }

    float getBodyRotation(int i) {
        sf::Vector2i previous = body[i-1];
        sf::Vector2i next = body[i+1];
        if (previous.y == next.y) {
            return 90;
        }
        return 0;
    }

    float getTailRotation() {
        sf::Vector2i tail = body.back();
        sf::Vector2i beforeTail = body[body.size() - 2];

        if (tail.x > beforeTail.x)
            return 270;
        if (tail.x < beforeTail.x)
            return 90;
        if (tail.y > beforeTail.y)
            return 0;
        if (tail.y < beforeTail.y)
            return 180;

        return 0;
    }

    float getCurveRotation(int i)
    {
        sf::Vector2i previous = body[i-1];
        sf::Vector2i current = body[i];
        sf::Vector2i next = body[i+1];

        if ((previous.y > current.y && next.x < current.x) ||
            (next.y > current.y && previous.x < current.x))
            return 0;

        if ((previous.y > current.y && next.x > current.x) ||
            (next.y > current.y && previous.x > current.x))
            return 270;

        if ((previous.y < current.y && next.x > current.x) ||
            (next.y < current.y && previous.x > current.x))
            return 180;

        return 90;
    }

    bool isCurve(int i) {
        sf::Vector2i before = body[i-1];
        sf::Vector2i current = body[i];
        sf::Vector2i after = body[i+1];

        bool horizontal = (before.x != current.x || after.x != current.x);
        bool vertical = (before.y != current.y || after.y != current.y);
        return horizontal && vertical;
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
    sf::Texture headTexture;
    sf::Texture bodyTexture;
    sf::Texture tailTexture;
    sf::Texture curveTexture;
};



#endif //SNAKE_HPP

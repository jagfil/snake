#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "Fruit.hpp"
#include "Game.hpp"

int main() {

Game game;

    while (game.isRunning()) {
        game.input();
        game.update();
        game.draw();
    }

    return 0;
}
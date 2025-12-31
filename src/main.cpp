#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Game.h"
#include "Logger.h"

#include <iostream>

int main() {
    
    Pacman::Game game;
    game.run();
    return 0;
}
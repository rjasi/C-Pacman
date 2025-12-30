#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Game.h"
#include "Logger.h"

#include <iostream>

int main() {
    
    sf::Window window(sf::VideoMode({800, 600}), "Pacman");
    window.setFramerateLimit(60);

    Pacman::Game game;
    game.foo(45);
    game.printLevel();
    auto& log = Pacman::Logger::instance();
    log.info("Hello");

    std::cout << "edefew";

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    }

    return 0;
}
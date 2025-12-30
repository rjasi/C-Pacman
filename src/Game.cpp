#include "Game.h"

#include <iostream>
#include <vector> 

namespace Pacman
{
    Game::Game()
    {
        lives = 3;
        bool success = level.loadFromFile("assets/level1.txt");
        if (!success)
        {
            std::cerr << "ERROR LOADING";
        }
    }

    void Game::printLevel()
    {
        std::vector<std::string> tiles = level.getTiles();
        for (const std::string& row : tiles)
        {
            std::cerr << row << "\n";
        }
    }

    void Game::foo(int& a)
    {
        std::cerr << " Game::foo(int& a)\n";
    }

    void Game::foo(const int& a)
    {
        std::cerr << " Game::foo(const int& a)\n";
    }
}
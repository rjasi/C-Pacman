#pragma once

namespace Pacman
{
    // TODO rename to GameCharacters
    enum class GameCharacters
    {
        Blinky,
        Pinky,
        Inky,
        Clyde,
        Pacman
    };

    namespace GameCharactersIndex
    {
        constexpr int BLINKY = static_cast<int>(GameCharacters::Blinky);
        constexpr int PINKY = static_cast<int>(GameCharacters::Pinky);
        constexpr int INKY = static_cast<int>(GameCharacters::Inky);
        constexpr int CLYDE = static_cast<int>(GameCharacters::Clyde);
        constexpr int PACMAN = static_cast<int>(GameCharacters::Pacman);
    }

    
}
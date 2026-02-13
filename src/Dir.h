#pragma once

#include "TileRC.h"

namespace Pacman
{
    enum class Dir
    {
        None = 0,
        Left,
        Right,
        Up,
        Down,
    };

    class DirUtils
    {
        public:
            DirUtils() = delete;

           static constexpr sf::Vector2f dirVecWorld(Dir d) 
            {
                switch (d) 
                {
                    case Dir::Right: return { 1.f,  0.f};
                    case Dir::Left:  return {-1.f,  0.f};
                    case Dir::Up:    return { 0.f, -1.f};
                    case Dir::Down:  return { 0.f,  1.f};
                    default:         return { 0.f,  0.f};
                }
            }

            static constexpr TileRC dirVecTile(Dir d) 
            {
                switch (d) 
                {
                    case Dir::Right: return { 0,  1};
                    case Dir::Left:  return { 0, -1};
                    case Dir::Up:    return {-1,  0};
                    case Dir::Down:  return { 1,  0};
                    default:         return { 0,  0};
                }
            }

            static constexpr Dir opposite(Dir d) 
            {
                switch (d) 
                {
                    case Dir::Up: 
                        return Dir::Down;
                    case Dir::Down: 
                        return Dir::Up;
                    case Dir::Left: 
                        return Dir::Right;
                    case Dir::Right: 
                        return Dir::Left;
                    default: 
                        return Dir::None;
                }
            }

            static constexpr bool isHorizontal(Dir d) 
            { 
                return d == Dir::Left || d == Dir::Right; 
            }

            static constexpr bool isVertical(Dir d)
            { 
                return d == Dir::Up || d == Dir::Down; 
            }
    };
    

}
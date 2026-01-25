#pragma once

#include "GhostEnum.h"
#include "Animation.h"

namespace Pacman
{
    class DirectionalAnimation
    {
        public:
            DirectionalAnimation(
                Animation* up,
                Animation* down,
                Animation* left,
                Animation* right
            ) 
            : up_(up), 
            down_(down), 
            left_(left), 
            right_(right)
            {

            }
            Animation* up_ = nullptr;
            Animation* down_ = nullptr;
            Animation* left_ = nullptr;
            Animation* right_ = nullptr;

            void update(sf::Time dt)
            {
                up_->update(dt);
                down_->update(dt);
                left_->update(dt);
                right_->update(dt);
            }

            Animation& clipFor(Dir d) 
            {
                switch (d) 
                {
                    case Dir::Up:    return *up_;
                    case Dir::Down:  return *down_;
                    case Dir::Left:  return *left_;
                    case Dir::Right: return *right_;
                    default:
                        return *up_;
                }
            }
    };
}
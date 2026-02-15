#pragma once

#include "GhostEnum.h"
#include "Animation.h"

namespace Pacman
{
    class DirectionalAnimation
    {
        private:
            bool single_ = false;

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
                single_ = false;
            }

            // for animations that are the same in any direction i.e frightened
            DirectionalAnimation(
                Animation* single
            ) 
            : up_(single), 
            down_(single), 
            left_(single), 
            right_(single)
            {
                single_ = true;
            }
            

            Animation* up_ = nullptr;
            Animation* down_ = nullptr;
            Animation* left_ = nullptr;
            Animation* right_ = nullptr;

            void update(sf::Time dt)
            {
                if (!single_)
                {
                    up_->update(dt);
                    down_->update(dt);
                    left_->update(dt);
                    right_->update(dt);
                }
                else
                {
                    up_->update(dt);
                }
                
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
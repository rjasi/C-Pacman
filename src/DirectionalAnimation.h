#pragma once

#include "GhostEnum.h"
#include "Animation.h"

namespace Pacman
{
    // stores animations each of the 4 directions sprites travel in pacman
    class DirectionalAnimation
    {
        private:
            bool single_ = false;

            // own animations
            Animation up_;
            Animation down_;
            Animation left_;
            Animation right_;
        public:
      

            Animation& up()
            {
                return up_;
            }

            Animation& down()
            {
                return down_;
            }

            Animation& left()
            {
                return left_;
            }

            Animation& right()
            {
                return right_;
            }



            DirectionalAnimation(
                const DirectionalAnimation& other
            ) 
            : up_(other.up_), 
            down_(other.down_), 
            left_(other.left_), 
            right_(other.right_),
            single_(other.single_)
            {
                // std::cerr << "DIR COPY\n";
            }



            DirectionalAnimation(
                Animation* up,
                Animation* down,
                Animation* left,
                Animation* right
            ) 
            : up_(*up), 
            down_(*down), 
            left_(*left), 
            right_(*right)
            {
                single_ = false;
            }

            DirectionalAnimation(
                DirArray<Animation>& animations
            ) 
            : up_(animations[Dir::Up]), 
            down_(animations[Dir::Down]), 
            left_(animations[Dir::Left]), 
            right_(animations[Dir::Right])
            {
                single_ = false;
            }

            DirectionalAnimation(
                const DirArray<Animation>& animations
            ) 
            : up_(animations[Dir::Up]), 
            down_(animations[Dir::Down]), 
            left_(animations[Dir::Left]), 
            right_(animations[Dir::Right])
            {
                single_ = false;
            }

            // for animations that are the same in any direction i.e frightened
            DirectionalAnimation(
                Animation* single
            ) 
            : up_(*single), 
            down_(*single), 
            left_(*single), 
            right_(*single)
            {
                single_ = true;
            }
            
            

            void update(sf::Time dt)
            {
                if (!single_)
                {
                    up_.update(dt);
                    down_.update(dt);
                    left_.update(dt);
                    right_.update(dt);
                }
                else
                {
                    up_.update(dt);
                }
                
            }

            Animation& clipFor(Dir d) 
            {
                switch (d) 
                {
                    case Dir::Up:    return up_;
                    case Dir::Down:  return down_;
                    case Dir::Left:  return left_;
                    case Dir::Right: return right_;
                    default:
                        return up_;
                }
            }
    };
}
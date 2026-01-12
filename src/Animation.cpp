#include "Animation.h"

namespace Pacman
{
    Animation::Animation(sf::Texture& texture,
                        const Atlas::AtlasRegion& region,
                        int frameCount,
                        sf::Time frameTime,
                        sf::Vector2f origin,
                        int row)
    : sprite_(texture), 
    region_(region), 
    frameCount_(frameCount),
    frameTime_(frameTime),
    row_(row)
    {
        sprite_.setOrigin(origin);
        apply();
    }

    void Animation::apply()
    {
        sprite_.setTextureRect(Atlas::frameRect(region_, current_, row_));
    }

    void Animation::reset() 
    { 
        current_ = 0; 
        elapsed_ = sf::Time::Zero; 
        apply(); 
    }

    void Animation::update(sf::Time dt)
    {
        if (frameCount_ <= 0) 
            return;

        elapsed_ += dt;
        while (elapsed_ >= frameTime_) 
        {
            elapsed_ -= frameTime_;
            current_ = (current_ + 1) % frameCount_;
            apply();
        }
    }

    void Animation::setRow(int row) 
    { 
        row_ = row; current_ = 0; 
        elapsed_ = sf::Time::Zero; 
        apply(); 
    }
        
    void Animation::setFrameCount(int n) 
    { 
        frameCount_ = n; current_ = 0; apply(); 
    }

    sf::Sprite& Animation::sprite()
    {
        return sprite_;
    }

}
#include "Animation.h"

#include <iostream>

namespace Pacman
{
    Animation::Animation(sf::Texture& texture,
                        const Atlas::AtlasRegion& region,
                        int frameCountRow,
                        sf::Time frameTime,
                        sf::Vector2f origin,
                        int row,
                        const std::vector<sf::IntRect>& additionalFrames)
    : sprite_(texture), 
    region_(region), 
    frameCount_(frameCountRow  + additionalFrames.size()),
    frameTime_(frameTime),
    row_(row)
    {
        frameRects_.reserve(frameCount_);
        for (int i = 0; i < frameCountRow; i++)
        {
            frameRects_.push_back(Atlas::frameRect(region_, i, row_));
        }

        frameRects_.insert(frameRects_.end(), additionalFrames.begin(), additionalFrames.end());

        sprite_.setOrigin(origin);
        // std::cerr << sprite().getPosition().length() << "ANIMATION construct \n";
        apply();
    }

    Animation::Animation(const Animation& other)
    : sprite_(other.sprite_)          // copies texture pointer + transform
    , region_(other.region_)
    , frameCount_(other.frameCount_)
    , row_(other.row_)
    , current_(0)                     // reset playback
    , elapsed_(sf::Time::Zero)        // reset playback
    , frameTime_(other.frameTime_)
    , frameRects_(other.frameRects_)
    {
        // std::cerr << "ANIMATION copy\n";
        apply(); // reset animation state
    }

    void Animation::apply()
    {
        sprite_.setTextureRect(frameRects_[current_]);
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
        frameCount_ = n; 
        current_ = 0; 
        apply(); 
    }

    sf::Sprite& Animation::sprite()
    {
        return sprite_;
    }

}
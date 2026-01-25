#include "AnimationLibrary.h"


namespace Pacman
{
    AnimationLibrary::AnimationLibrary(TextureCache& cache)
    : 
    pacmanRight_(cache.get("atlas"), Atlas::PacmanRight, 3, sf::milliseconds(60)),

    blinkyRight_(cache.get("atlas"), Atlas::BlinkyRight, 2, ghostFrameTime),
    blinkyLeft_(cache.get("atlas"), Atlas::BlinkyLeft, 2, ghostFrameTime),
    blinkyUp_(cache.get("atlas"), Atlas::BlinkyUp, 2, ghostFrameTime),
    blinkyDown_(cache.get("atlas"), Atlas::BlinkyDown, 2, ghostFrameTime),

    pinkyRight_(cache.get("atlas"), Atlas::PinkyRight, 2, ghostFrameTime),
    pinkyLeft_(cache.get("atlas"), Atlas::PinkyLeft, 2, ghostFrameTime),
    pinkyUp_(cache.get("atlas"), Atlas::PinkyUp, 2, ghostFrameTime),
    pinkyDown_(cache.get("atlas"), Atlas::PinkyDown, 2, ghostFrameTime),

    inkyRight_(cache.get("atlas"), Atlas::InkyRight, 2, ghostFrameTime),
    inkyLeft_(cache.get("atlas"), Atlas::InkyLeft, 2, ghostFrameTime),
    inkyUp_(cache.get("atlas"), Atlas::InkyUp, 2, ghostFrameTime),
    inkyDown_(cache.get("atlas"), Atlas::InkyDown, 2, ghostFrameTime),

    clydeRight_(cache.get("atlas"), Atlas::ClydeRight, 2, ghostFrameTime),
    clydeLeft_(cache.get("atlas"), Atlas::ClydeLeft, 2, ghostFrameTime),
    clydeUp_(cache.get("atlas"), Atlas::ClydeUp, 2, ghostFrameTime),
    clydeDown_(cache.get("atlas"), Atlas::ClydeDown, 2, ghostFrameTime),
    
    pacman_normal(&pacmanRight_, &pacmanRight_, &pacmanRight_, &pacmanRight_),
    blinky_normal(&blinkyUp_, &blinkyDown_, &blinkyLeft_, &blinkyRight_),
    pinky_normal(&pinkyUp_, &pinkyDown_, &pinkyLeft_, &pinkyRight_),
    inky_normal(&inkyUp_, &inkyDown_, &inkyLeft_, &inkyRight_),
    clyde_normal(&clydeUp_, &clydeDown_, &clydeLeft_, &clydeRight_),

    pacman(&pacman_normal),
    blinky(GameCharacters::Blinky, &blinky_normal),
    pinky(GameCharacters::Pinky, &pinky_normal),
    inky(GameCharacters::Inky, &inky_normal),
    clyde(GameCharacters::Clyde, &clyde_normal)
    {
        ghostResolvers_[GameCharactersIndex::BLINKY] = std::make_unique<GhostAnimationResolver>(&blinky);
        ghostResolvers_[GameCharactersIndex::PINKY] = std::make_unique<GhostAnimationResolver>(&pinky);
        ghostResolvers_[GameCharactersIndex::INKY] = std::make_unique<GhostAnimationResolver>(&inky);
        ghostResolvers_[GameCharactersIndex::CLYDE] = std::make_unique<GhostAnimationResolver>(&clyde);

        pacmanResolver_ = std::make_unique<PacmanAnimationResolver>(&pacman);
    }


    void AnimationLibrary::update(sf::Time dt)
    {
        pinky.update(dt);
        inky.update(dt);
        blinky.update(dt);
        clyde.update(dt);
    }
}
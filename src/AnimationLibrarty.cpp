#include "AnimationLibrary.h"


namespace Pacman
{
    AnimationLibrary::AnimationLibrary(TextureCache& cache)
    : pacmanRight_(cache.get("atlas"), Atlas::PacmanRight, 3, sf::milliseconds(60)),

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
    clydeDown_(cache.get("atlas"), Atlas::ClydeDown, 2, ghostFrameTime)
    {
        blinky = {
            .right = &blinkyRight_,
            .left = &blinkyLeft_,
            .up = &blinkyUp_,
            .down = &blinkyDown_
        };

        pinky = {
            .right = &pinkyRight_,
            .left = &pinkyLeft_,
            .up = &pinkyUp_,
            .down = &pinkyDown_
        };

        inky = {
            .right = &inkyRight_,
            .left = &inkyLeft_,
            .up = &inkyUp_,
            .down = &inkyDown_
        };

        clyde = {
            .right = &clydeRight_,
            .left = &clydeLeft_,
            .up = &clydeUp_,
            .down = &clydeDown_
        };
    }


    void AnimationLibrary::update(sf::Time dt)
    {
        pinky.update(dt);
        inky.update(dt);
        blinky.update(dt);
        clyde.update(dt);
    }
}
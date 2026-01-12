#include "AnimationLibrary.h"


namespace Pacman
{
    AnimationLibrary::AnimationLibrary(TextureCache& cache)
    : pacmanRight_(cache.get("atlas"), Atlas::PacmanRight, 3, sf::milliseconds(60), {8.0f, 8.0f}),
    blinkyRight_(cache.get("atlas"), Atlas::BlinkyRight, 3, sf::milliseconds(60), {8.0f, 8.0f})
    {
    }

    void AnimationLibrary::loadAll(TextureCache& cache)
    {
        // atlas_ = c&cache.get("atlas");
        // pacmanRight_ = Animation(cache.get("atlas");, Atlas::PacmanRight, 3, sf::milliseconds(60));
        // blinkyRight_ = Animation(cache.get("atlas"), Atlas::BlinkyRight, 2, sf::milliseconds(60));
    }
}
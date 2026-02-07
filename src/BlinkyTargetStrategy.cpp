#include "BlinkyTargetStrategy.h"

namespace Pacman
{
    BlinkyTargetStrategy::BlinkyTargetStrategy(const sf::Vector2i& corner)
    : corner_(corner)
    {

    }

    // Blinky always goes for pacman's current location
    sf::Vector2i BlinkyTargetStrategy::getTarget(const TargetContext& ctx) const
    {
        return ctx.pacman_tile;
    }

    sf::Vector2i BlinkyTargetStrategy::scatterTarget(const TargetContext& ctx) const
    {
        return corner_;
    }
}
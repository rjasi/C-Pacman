#include "BlinkyTargetStrategy.h"

namespace Pacman
{
    BlinkyTargetStrategy::BlinkyTargetStrategy(const TileRC& corner)
    : corner_(corner)
    {

    }

    // Blinky always goes for pacman's current location
    TileRC BlinkyTargetStrategy::getTarget(const TargetContext& ctx) const
    {
        return ctx.pacman_tile;
    }

    TileRC BlinkyTargetStrategy::scatterTarget(const TargetContext& ctx) const
    {
        return corner_;
    }
}
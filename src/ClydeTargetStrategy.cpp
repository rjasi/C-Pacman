#include "ClydeTargetStrategy.h"
#include "PathUtils.h"


namespace Pacman
{
    ClydeTargetStrategy::ClydeTargetStrategy(const TileRC& corner)
    : corner_(corner)
    {

    }

    TileRC ClydeTargetStrategy::getTarget(const TargetContext& ctx) const
    {
        // if dist between clyde and pacman <= 8 tiles then chase pacman otherwise scatter
        if (PathUtils::euclidianDistanceSquared(ctx.pacman_tile, ctx.clyde_tile) <= 64)
        {
            return ctx.pacman_tile;
        } 

        return scatterTarget(ctx);
    }

    TileRC ClydeTargetStrategy::scatterTarget(const TargetContext& ctx) const
    {
        return corner_;
    }
}
#include "PinkyTargetStrategy.h"


namespace Pacman
{
    PinkyTargetStrategy::PinkyTargetStrategy(const TileRC& corner)
    : corner_(corner)
    {
    
    }

    TileRC PinkyTargetStrategy::getTarget(const TargetContext& ctx) const
    {
        // target 4 tiles ahead of pacman. If wall or out of bounds does not matter
        // as path finding algorithm is greedy manhatten distance
        return ctx.pacman_tile + DirUtils::dirVecTile(ctx.pacman_dir) * 4;
    }

    TileRC PinkyTargetStrategy::scatterTarget(const TargetContext& ctx) const
    {
        return corner_;
    }
}
#include "InkyTargetStrategy.h"

namespace Pacman
{
    InkyTargetStrategy::InkyTargetStrategy(const TileRC& corner)
    : corner_(corner)
    {

    }

    TileRC InkyTargetStrategy::getTarget(const TargetContext& ctx) const
    {
        // target 2 tiles ahead of pacman, then draw vector from blinky to that tile. then double it
        TileRC aheadPacman = ctx.pacman_tile + DirUtils::dirVecTile(ctx.pacman_dir) * 2;
        TileRC vector = aheadPacman - ctx.blinky_tile;
        return ctx.blinky_tile + vector * 2;

    }

    TileRC InkyTargetStrategy::scatterTarget(const TargetContext& ctx) const
    {
        return corner_;
    }
}
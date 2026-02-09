#pragma once

#include "IGhostTargetStrategy.h"

namespace Pacman
{
    class ClydeTargetStrategy : public IGhostTargetStrategy
    {
        private:
            TileRC corner;
        public:
            TileRC getTarget(const TargetContext& ctx) const override;
            TileRC scatterTarget(const TargetContext& ctx) const override;
    };
}
#pragma once

#include "IGhostTargetStrategy.h"

namespace Pacman
{
    class PinkyTargetStrategy : public IGhostTargetStrategy
    {
        private:
            TileRC corner_;
        public:
            PinkyTargetStrategy(const TileRC& corner);
            TileRC getTarget(const TargetContext& ctx) const override;
            TileRC scatterTarget(const TargetContext& ctx) const override;
    };
}
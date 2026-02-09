#pragma once

#include "IGhostTargetStrategy.h"

namespace Pacman
{
    class BlinkyTargetStrategy : public IGhostTargetStrategy
    {
        private:
            TileRC corner_;
        public:
            explicit BlinkyTargetStrategy(const TileRC& corner);
            TileRC getTarget(const TargetContext& ctx) const override;
            TileRC scatterTarget(const TargetContext& ctx) const override;
    };
}
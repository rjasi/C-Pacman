#pragma once

#include "IGhostTargetStrategy.h"

namespace Pacman
{
    class InkyTargetStrategy : public IGhostTargetStrategy
    {
        private:
            TileRC corner_;
        public:
            InkyTargetStrategy(const TileRC& corner);
            TileRC getTarget(const TargetContext& ctx) const override;
            TileRC scatterTarget(const TargetContext& ctx) const override;
    };
}
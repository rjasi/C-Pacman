#pragma once

#include "IGhostTargetStrategy.h"

namespace Pacman
{
    class ClydeTargetStrategy : public IGhostTargetStrategy
    {
        private:
            sf::Vector2i corner;
        public:
            sf::Vector2i getTarget(const TargetContext& ctx) const override;
            sf::Vector2i scatterTarget(const TargetContext& ctx) const override;
    };
}
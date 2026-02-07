#pragma once

#include "IGhostTargetStrategy.h"

namespace Pacman
{
    class BlinkyTargetStrategy : public IGhostTargetStrategy
    {
        private:
            sf::Vector2i corner_;
        public:
            explicit BlinkyTargetStrategy(const sf::Vector2i& corner);
            sf::Vector2i getTarget(const TargetContext& ctx) const override;
            sf::Vector2i scatterTarget(const TargetContext& ctx) const override;
    };
}
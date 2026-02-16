#pragma once 

#include "AtlasRegion.h"
#include "Popup.h"
#include "TextureCache.h"

#include <optional>

#include <SFML/Graphics.hpp>


namespace Pacman
{
    class ScorePopupRenderer
    {
        private:
            sf::Sprite scoreSprite_;
            static std::optional<Atlas::AtlasRegion> frameFor(Scores score);
            
        public:
            ScorePopupRenderer(TextureCache& cache);
            void render(sf::RenderTarget& window, const ScorePopup& popup);
            
    };
}
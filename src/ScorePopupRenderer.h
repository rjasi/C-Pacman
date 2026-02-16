#pragma once 

#include "AtlasRegion.h"
#include "Popup.h"
#include "TextureCache.h"

#include <SFML/Graphics.hpp>


namespace Pacman
{
    class ScorePopupRenderder
    {
        private:
            sf::Sprite scoreSprite_;
            // sf::Sprite score400Sprite_;
            // sf::Sprite score800Sprite_;
            // sf::Sprite score1600Sprite_;

        public:
            ScorePopupRenderder(TextureCache& cache);
            void render(sf::RenderTarget& window, const ScorePopup& popup);
            
    };
}
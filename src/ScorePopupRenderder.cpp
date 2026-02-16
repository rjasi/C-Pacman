#include "ScorePopupRenderer.h"

#include <iostream>

namespace Pacman
{
    ScorePopupRenderer::ScorePopupRenderer(TextureCache& cache)
    : scoreSprite_(cache.get("atlas"))
    {

    }

    void ScorePopupRenderer::render(sf::RenderTarget& window, const ScorePopup& popup)
    {
        auto result = frameFor(popup.score);
        if (!result) return;

        Atlas::AtlasRegion frameRegion = *result;

        scoreSprite_.setTextureRect(Atlas::frameRect(frameRegion));
        scoreSprite_.setOrigin({frameRegion.frameSize / 2}); 
        scoreSprite_.setPosition(popup.pos);
        window.draw(scoreSprite_);
    }

    
    
    std::optional<Atlas::AtlasRegion> ScorePopupRenderer::frameFor(Scores score)
    {
        switch (score)
        {
            case Scores::BlueScore200:  return Atlas::BlueScore200;
            case Scores::BlueScore400:  return Atlas::BlueScore400;
            case Scores::BlueScore800:  return Atlas::BlueScore800;
            case Scores::BlueScore1600: return Atlas::BlueScore1600;
            default:                    return std::nullopt;
        }
    }

}
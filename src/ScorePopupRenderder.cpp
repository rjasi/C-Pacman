#include "ScorePopupRenderer.h"

#include <iostream>

namespace Pacman
{
    ScorePopupRenderder::ScorePopupRenderder(TextureCache& cache)
    : scoreSprite_(cache.get("atlas"))
    {

    }

    void ScorePopupRenderder::render(sf::RenderTarget& window, const ScorePopup& popup)
    {
        switch (popup.score)
        {
            case Scores::BlueScore200:
                scoreSprite_.setTextureRect(Atlas::frameRect(Atlas::BlueScore200));
                scoreSprite_.setOrigin({Atlas::BlueScore200.frameSize / 2}); // center origin
                break;
            case Scores::BlueScore400:
                scoreSprite_.setTextureRect(Atlas::frameRect(Atlas::BlueScore400));
                scoreSprite_.setOrigin({Atlas::BlueScore200.frameSize / 2});
                break;
            case Scores::BlueScore800:
                scoreSprite_.setTextureRect(Atlas::frameRect(Atlas::BlueScore800));
                scoreSprite_.setOrigin({Atlas::BlueScore200.frameSize / 2});
                break;
            case Scores::BlueScore1600:

                scoreSprite_.setTextureRect(Atlas::frameRect(Atlas::BlueScore1600));
                scoreSprite_.setOrigin({Atlas::BlueScore200.frameSize / 2});
                break;
            default:
                return;
        }

        scoreSprite_.setPosition(popup.pos);
        window.draw(scoreSprite_);
    }

}
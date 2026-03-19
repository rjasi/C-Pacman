#pragma once

#include "AnimationLibrary.h"
#include "Renderable.h"
#include "GhostEnum.h"
#include "TextureCache.h"
#include "World.h"
#include "TileFontLibrary.h"
#include "ScorePopupRenderer.h"
#include "ScreenConfig.h"
#include "UiLayout.h"
#include "CutsceneLibrary.h"
#include "CutscenePlayer.h"
#include "CutsceneEnum.h"

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>
#include <vector>

namespace Pacman
{
    class GameView 
    {
        public:
            GameView() = delete;
            explicit GameView(TextureCache& cache, 
                AnimationLibrary* animationLibrary,
                TileFontLibrary* tileFontLibrary,
                ScorePopupRenderer* scorePopupRenderer,
                GameAudio& gameAudio);
            void reset();
            void update(sf::Time dt);
            void render(sf::RenderTarget& window);
            void handleEvent(const sf::Event& event);

        private:
            TextureCache& textCache_;

            sf::View worldView_;
            sf::Sprite mazeSprite_;
            sf::Sprite mazeNoDoorBlueSprite_;
            sf::Sprite mazeNoDoorWhiteSprite_;

            sf::Sprite pelletSprite_;
            sf::Sprite powerPelletSprite_;
            sf::Sprite pacmanLivesSprite_;

            std::vector<Renderable> renderables_;
            GameAudio& gameAudio_;
            World world_;
            UiLayout uiLayout_;
            AnimationLibrary* animationLibrary_;
            TileFontLibrary* tileFontLibrary_;
            ScorePopupRenderer* scorePopupRenderer_;
            CutscenePlayer cutscenePlayer_;
            bool assetsLoaded_ = false;

            void loadAssets();
            void drawPellets(sf::RenderTarget& window);
            void drawPopup(sf::RenderTarget& window, const TextPopup& popup);
            void drawPopup(sf::RenderTarget& window, const ScorePopup& popup);
            void drawUi(sf::RenderTarget& window);
            void drawCutscene(sf::RenderTarget& window);
    };
}
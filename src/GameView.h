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
    enum class ScreenMode
    {
        Intro,
        PushStart,
        Playing
    };

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
            ScreenMode screenMode_ = ScreenMode::Intro;
            TextureCache& textCache_;

            sf::View worldView_;
            sf::Sprite mazeSprite_;
            sf::Sprite mazeNoDoorBlueSprite_;
            sf::Sprite mazeNoDoorWhiteSprite_;

            sf::Sprite pelletSprite_;
            sf::Sprite powerPelletSprite_;
            sf::Sprite pacmanLivesSprite_;

            sf::Sprite cherrySprite_;
            sf::Sprite strawberrySprite_;
            sf::Sprite peachSprite_;
            sf::Sprite appleSprite_;
            sf::Sprite grapesSprite_;
            sf::Sprite galaxianSprite_;
            sf::Sprite bellSprite_;
            sf::Sprite keySprite_;

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
            void drawFruit(sf::RenderTarget& window);
            void drawIntro(sf::RenderTarget& window);
            void drawPushStart(sf::RenderTarget& window);
            void drawPlaying(sf::RenderTarget& window);
            void updatePlaying(sf::Time dt);
            void updateIntro(sf::Time dt);
            sf::Sprite& getFruitSprite(Fruits fruit);
            void drawUiFruits(sf::RenderTarget& window);
            // main menu 
            sf::Time menuTimer_;

            sf::Sprite blinkyMenuSprite_;
            sf::Sprite pinkyMenuSprite_;
            sf::Sprite inkyMenuSprite_;
            sf::Sprite clydeMenuSprite_;

            static constexpr sf::Time blinkyMenuSpriteTime_ = sf::seconds(1.f);
            static constexpr sf::Time blinkyCharacterTextTime_ = blinkyMenuSpriteTime_ + sf::seconds(1.0f);
            static constexpr sf::Time blinkyNicknameTextTime_ = blinkyCharacterTextTime_ + sf::seconds(.4f);

            static constexpr sf::Time pinkyMenuSpriteTime_ = blinkyNicknameTextTime_ + sf::seconds(.4f);
            static constexpr sf::Time pinkyCharacterTextTime_ = pinkyMenuSpriteTime_ + sf::seconds(1.0f);
            static constexpr sf::Time pinkyNicknameTextTime_ = pinkyCharacterTextTime_ + sf::seconds(.4f);

            static constexpr sf::Time inkyMenuSpriteTime_ = pinkyNicknameTextTime_ + sf::seconds(.4f);
            static constexpr sf::Time inkyCharacterTextTime_ = inkyMenuSpriteTime_ + sf::seconds(1.0f);
            static constexpr sf::Time inkyNicknameTextTime_ = inkyCharacterTextTime_ + sf::seconds(.4f);
            
            static constexpr sf::Time clydeMenuSpriteTime_ = inkyNicknameTextTime_ + sf::seconds(.4f);
            static constexpr sf::Time clydeCharacterTextTime_ = clydeMenuSpriteTime_ + sf::seconds(1.0f);
            static constexpr sf::Time clydeNicknameTextTime_ = clydeCharacterTextTime_ + sf::seconds(.4f);
            
            static constexpr sf::Time ptsSpriteTime_ = clydeCharacterTextTime_ + sf::seconds(1.f);
            static constexpr sf::Time namcoTimer_ = ptsSpriteTime_ + sf::seconds(1.f);

    };
}
#pragma once

#include "Ghost.h"
#include "Maze.h"
#include "MoveableEntity.h"
#include "GhostTargetStrategies.h"
#include "GreedyManhattanPathingStrategy.h"
#include "LevelConfig.h"
#include "GhostDirector.h"
#include "TextColors.h"
#include "Popup.h"
#include "ScreenConfig.h"
#include "GameAudio.h"
#include "SfxId.h"
#include "CutsceneEnum.h"
#include "FruitEnum.h"

#include <cstdint>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>


namespace Pacman
{
    enum class WorldState
    {
        Playing = 0,
        GhostEaten,
        Died,
        LevelCleared,
        Cutscene,
        NewGame,
        RestartLevel,
    };

    enum class MazeDisplayMode
    {
        Normal = 0,
        NoDoorBlue,
        NoDoorWhite
    };

    // class GhostEatenContext
    // {
    //     public:
    //         sf::Vector2f pos;
    // };

    class World
    {
        private:
            int level_ = 1;

            Ghost* eatenGhost = nullptr;
            WorldState state_ = WorldState::NewGame;
            WorldState nextState_ = WorldState::Playing;

            Maze maze_;
            MoveableEntity pacmanEntity_;
            Ghost blinky_;
            Ghost pinky_;
            Ghost inky_;
            Ghost clyde_;
            BlinkyTargetStrategy blinkyTargetStrategy_;
            PinkyTargetStrategy pinkyTargetStrategy_;
            InkyTargetStrategy inkyTargetStrategy_;
            ClydeTargetStrategy clydeTargetStrategy_;
            LevelConfig cfg_;
            GhostDirector ghostDirector_;
            GameAudio gameAudio_;
            Cutscenes requestedCutscene_ = Cutscenes::None;
            Cutscenes activeCutscene_ = Cutscenes::None;
            MazeDisplayMode mazeDisplayMode_ = MazeDisplayMode::Normal;            

            bool flipWaka = false;
            
            std::vector<TextPopup> textPopups_;
            std::vector<ScorePopup> scorePopups_;


            // ingame cutscene related details
            // ________________________________
            
            // ghost eaten pause for 1 sec 
            static constexpr sf::Time EATEN_PAUSE = sf::seconds(1.0f);
            sf::Time eatenTimer_{};

            // new game
            static constexpr sf::Time NEW_GAME_INTRO = sf::seconds(4.2f);
            static constexpr sf::Time NEW_GAME_INTRO_SPAWN_CHARACTER_TIME= sf::seconds(3.0f);
            sf::Time startNewGameTimer_{};

            // died
            static constexpr sf::Time DIED_ANIM_START_TIME = sf::seconds(2.f);
            static constexpr sf::Time DIED_STATE_TIME= sf::seconds(5.0f);
            sf::Time diedTimer_{};

            // restart level timer
            static constexpr sf::Time RESTART_LEVEL_PAUSE_TIME = sf::seconds(3.f);
            sf::Time restartLevelTimer_{};

            // level cleared

            // phase 1 pacman is circle and everything is frozen
            static constexpr sf::Time LEVEL_CLEARED_PHASE_1 = sf::seconds(2.f);
            // phase 2 flash maze
            static constexpr sf::Time MAZE_FLASH_TIME = sf::seconds(0.20f);
            static constexpr sf::Time LEVEL_CLEARED_PHASE_2 = sf::seconds(1.6f); // 8 * MAZE_FLASH_TIME, display 4 of white and  blue maze


            sf::Time levelClearedPhase1Timer_{};
            sf::Time levelClearedPhase2Timer_{};

            sf::Time flashMazeTimer_{};
            sf::Time blackScreenTime{};
            // ________________________________



            GreedyManhattanPathingStrategy greedyManhattanPathingStrategy_;

            static constexpr TileRC BLINKY_SCATTER_CORNER = {-3, 27};
            static constexpr TileRC PINKY_SCATTER_CORNER = {-3, 0};
            static constexpr TileRC INKY_SCATTER_CORNER = {31, 27};
            static constexpr TileRC CLYDE_SCATTER_CORNER = {31, 0};
            

            // fruit
            static constexpr sf::Time FRUIT_SPAWN_TIME = sf::seconds(10.f);
            static constexpr sf::Time FRUIT_POPUP_TIME = sf::seconds(2.f);
            static constexpr int FIRST_FRUIT_SPAWN_DOT_COUNT = 70;
            static constexpr int SECOND_FRUIT_SPAWN_DOT_COUNT = 170;
            sf::Time fruitTimer_{};
            Fruits spawnedFruit_ = Fruits::None;
            sf::Vector2f fruitPos_;

            // power pellet blinking
            sf::Time blinkElapsed_ = sf::Time::Zero;
            sf::Time blinkPeriod_  = sf::milliseconds(150); 
            bool powerPelletVisible_ = true;
            int highScore_ = 0;
            int score_ = 0;
            int lives_ = 3;
            int dotsEaten_ = 0;

            void resolveCollision();
            void playing(sf::Time dt);
            void newGame(sf::Time dt);
            void died(sf::Time dt);
            void ghostEaten(sf::Time dt);
            void restartLevel(sf::Time dt);
            void levelCleared(sf::Time dt);

            void advanceBlinkTimer(sf::Time dt);
            void updatePopups(sf::Time dt);
            int getGhostEatenScore(int ghostsEaten) const;
            Scores getGhostEatenScoreType(int ghostsEaten) const;
            bool anyGhostReturningHome() const;
            void setBGM();
            void advanceNextLevel();
            void resetEntities();
            void handleFruit(sf::Time dt);
            int getFruitScore() const;
            Scores getFruitScorePopup() const;

            void setEntitySpeeds();

        public:
            static constexpr int LAST_FRUIT_LEVEL = 13;
            Fruits getFruitForLevel(int level) const;

            World() = delete;
            World(GameAudio& gameAudio);

            const Maze& maze() const;
            const MoveableEntity& pacman() const;
            const MoveableEntity& blinky() const;
            const MoveableEntity& pinky() const;
            const MoveableEntity& inky() const;
            const MoveableEntity& clyde() const;

            bool powerPelletVisible() const;
            void setPlayerRequestedDir(Dir d);
            void update(sf::Time dt); 
            WorldState state() const;
            const std::vector<TextPopup>& textPopups() const;
            const std::vector<ScorePopup>& scorePopups() const;
            int score() const;
            int lives() const;
            int level() const;
            void notifyCutsceneStarted();
            void notifyCutsceneFinished();
            Cutscenes requestedCutscene() const;
            Cutscenes activeCutscene() const;

            void setStartNewGame();
            MazeDisplayMode mazeDisplayMode() const;

            Fruits spawnedFruit() const;
            const sf::Vector2f& fruitPos() const;
            const int highScore() const;

    };
}
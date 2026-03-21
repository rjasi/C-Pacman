#include "World.h"


#include <iostream>

namespace Pacman
{
    World::World(GameAudio& gameAudio) 
    :
    gameAudio_(),
    maze_(ScreenConfig::MazeOrigin),
    blinkyTargetStrategy_(BLINKY_SCATTER_CORNER),
    pinkyTargetStrategy_({PINKY_SCATTER_CORNER}),
    inkyTargetStrategy_({INKY_SCATTER_CORNER}),
    clydeTargetStrategy_({CLYDE_SCATTER_CORNER}),
    pacmanEntity_({Maze::PACMAN_SPAWN_POINT}, maze_.tileToWorldOnBoundary(Maze::PACMAN_SPAWN_POINT)),
    blinky_(blinkyTargetStrategy_, greedyManhattanPathingStrategy_, GameCharacters::Blinky, Maze::HOUSE_CENTER, Maze::INFRONT_DOOR_LEFT, maze_.tileToWorldOnBoundary(Maze::INFRONT_DOOR_LEFT)),
    pinky_(pinkyTargetStrategy_, greedyManhattanPathingStrategy_, GameCharacters::Pinky, Maze::HOUSE_CENTER, Maze::HOUSE_CENTER, maze_.tileToWorldOnBoundary(Maze::HOUSE_CENTER)),
    inky_(inkyTargetStrategy_, greedyManhattanPathingStrategy_, GameCharacters::Inky, Maze::HOUSE_LEFT, Maze::HOUSE_CENTER, maze_.tileToWorldOnBoundary(Maze::HOUSE_LEFT)),
    clyde_(clydeTargetStrategy_, greedyManhattanPathingStrategy_, GameCharacters::Clyde, Maze::HOUSE_RIGHT, Maze::HOUSE_CENTER, maze_.tileToWorldOnBoundary(Maze::HOUSE_RIGHT)),
    ghostDirector_(cfg_)
    {
        blinky_.setState(GhostState::Chase);
        blinky_.setHouseState(HouseState::Outside);
        blinky_.setDirection(Dir::Left);
        blinky_.setVisible(false);

        pinky_.setDirection(Dir::Down);
        pinky_.setHouseState(HouseState::InHouse);
        pinky_.setVisible(false);
        
        inky_.setDirection(Dir::Up);
        inky_.setHouseState(HouseState::InHouse);
        inky_.setVisible(false);

        clyde_.setDirection(Dir::Up);
        clyde_.setHouseState(HouseState::InHouse);
        clyde_.setVisible(false);

        pacmanEntity_.setVisible(false);

        fruitPos_ = maze_.tileToWorldOnBoundary(Maze::FRUIT_TILE);
    }

    void World::setPlayerRequestedDir(Dir d)
    {
        pacmanEntity_.requestDirection(d);
    }

    const MoveableEntity& World::pinky() const
    {
        return pinky_;
    }

    const MoveableEntity& World::inky() const
    {
        return inky_;
    }

    const MoveableEntity& World::clyde() const
    {
        return clyde_;
    }

    void World::update(sf::Time dt)
    {

        switch (state_)
        {
            case WorldState::Playing:
                advanceBlinkTimer(dt);
                playing(dt);
                break;
            case WorldState::GhostEaten:
                advanceBlinkTimer(dt);
                ghostEaten(dt);
                break;
            case WorldState::Cutscene:
                return; // do nothing, gameView will notify when cutscene has finished
            case WorldState::NewGame:
                newGame(dt);
                break;
            case WorldState::Died:
                advanceBlinkTimer(dt);  
                died(dt);
                break;
            case WorldState::RestartLevel:
                restartLevel(dt);
                break;
            case WorldState::LevelCleared:
                levelCleared(dt);
                break;
            default:
                return;
        }
    }

    // briefly pause the game when ghost is eaten and show a popup of the score
    void World::ghostEaten(sf::Time dt)
    {
        updatePopups(dt);
        eatenTimer_ += dt;
        if (eatenTimer_ >= EATEN_PAUSE)
        {
            state_ = WorldState::Playing;
            if (eatenGhost != nullptr)
            {
                eatenGhost->setVisible(true);
            }
            pacmanEntity_.setVisible(true);
            eatenGhost = nullptr;
            eatenTimer_ = sf::Time{};
        }
    }

    void World::advanceBlinkTimer(sf::Time dt)
    {
        blinkElapsed_ += dt;
        if (blinkElapsed_ >= blinkPeriod_) 
        {
            blinkElapsed_ -= blinkPeriod_;
            powerPelletVisible_ = !powerPelletVisible_;
        }
    }

    void World::playing(sf::Time dt)
    {
        updatePopups(dt);
        pacmanEntity_.update(dt, maze_);
        setBGM();
        handleFruit(dt);

        if (maze_.tryEatPellet(pacmanEntity_.position()))
        {
            dotsEaten_++;

            if (dotsEaten_ >= Maze::TOTAL_DOTS)
            {
                state_ = WorldState::LevelCleared;
                return;
            }

            gameAudio_.pauseMusic();
            score_ += 10;
            ghostDirector_.pelletEaten();
            flipWaka ? gameAudio_.playSfx(SfxId::Waka1): gameAudio_.playSfx(SfxId::Waka2);
            flipWaka = !flipWaka;
        }

        if (maze_.tryEatPowerPellet(pacmanEntity_.position()))
        {
            score_ += 50;
            dotsEaten_++;
            ghostDirector_.powerPelletEaten();
        }

        if (spawnedFruit_ != Fruits::None && maze_.tryEatFruit(pacmanEntity_.position()))
        {
            gameAudio_.pauseMusic();
            score_ += getFruitScore();
            scorePopups_.push_back(ScorePopup{maze_.tileToWorldOnBoundary(Maze::FRUIT_TILE), EATEN_PAUSE, 
                        getFruitScorePopup()});
            spawnedFruit_ = Fruits::None;
            gameAudio_.playSfx(SfxId::EatFruit);
        }

        TargetContext ctx
        {
            .pacman_tile = maze_.worldToTile(pacmanEntity_.position()),
            .pacman_dir = pacmanEntity_.direction(),
            .blinky_tile = maze_.worldToTile(blinky_.position()),
            .clyde_tile = maze_.worldToTile(clyde_.position())
        };

        ghostDirector_.update({&blinky_, &pinky_, &inky_, &clyde_}, maze_, ctx, dt);
        resolveCollision();
    }

    const Maze& World::maze() const
    {
        return maze_;
    }

    const MoveableEntity& World::pacman() const
    {
        return pacmanEntity_;
    }

    bool World::powerPelletVisible() const
    {
        return powerPelletVisible_;
    }

    const MoveableEntity& World::blinky() const
    {
        return blinky_;
    }

    void World::resolveCollision()
    {
        if (state_ != WorldState::Playing)
        {
            return; 
        }

        TileRC pacmanTile = maze_.worldToTile(pacmanEntity_.position());

        for (Ghost& ghost : { std::ref(blinky_), std::ref(pinky_),
                      std::ref(inky_), std::ref(clyde_) })
        {
            TileRC ghostTile = maze_.worldToTile(ghost.position());

            if (pacmanTile == ghostTile)
            {
                // causes weird inbettwen state if eaten in the middle of exiting house
                if (!ghost.isOutsideHouse())
                {
                    continue;
                }
                else if (ghost.state() == GhostState::Chase || ghost.state() == GhostState::Scatter)
                {
                    // lives_--;
                    // state_ = WorldState::Died;
                    return;
                }
                else if (ghost.state() == GhostState::Frightened)
                {

                    ghostDirector_.ghostEaten();
                    scorePopups_.push_back(ScorePopup{maze_.tileCenter(pacmanTile), EATEN_PAUSE, 
                        getGhostEatenScoreType(ghostDirector_.ghostEatenCount())});
                    state_ = WorldState::GhostEaten;
                    // todo maybe have ghost director change the state
                    ghost.setState(GhostState::EatenReturning);
                    eatenGhost = &ghost;
                    eatenTimer_ = sf::Time{};
                    pacmanEntity_.setVisible(false);
                    ghost.setVisible(false);
                    score_ += getGhostEatenScore(ghostDirector_.ghostEatenCount());
                    gameAudio_.playSfx(SfxId::EatGhost);
                    gameAudio_.pauseMusic();
                    return;
                }  
            }

            state_ = WorldState::Playing;
            eatenGhost = nullptr;
        }
    }

    WorldState World::state() const
    {
        return state_;
    }

    const std::vector<TextPopup>& World::textPopups() const
    {
        return textPopups_;
    }

    const std::vector<ScorePopup>& World::scorePopups() const
    {
        return scorePopups_;
    }

    Scores World::getGhostEatenScoreType(int ghostsEaten) const
    {
        switch (ghostsEaten)
        {
            case 1:
                return Scores::BlueScore200;
            case 2:
                return Scores::BlueScore400;
            case 3:
                return Scores::BlueScore800;
            // 4 or more is 1600. This would catch 0 too but impossile to be called with 0
            // this function is only call when a ghost is eaten so minimum is 1
            default:
                return Scores::BlueScore1600;
        }
    }

    int World::getGhostEatenScore(int ghostsEaten) const
    {
        switch (ghostsEaten)
        {
            case 1:
                return 200;
            case 2:
                return 400;
            case 3:
                return 800;
            // 4 or more is 1600. This would catch 0 too but impossile to be called with 0
            // this function is only call when a ghost is eaten so minimum is 1
            default:
                return 1600;
        }
    }

    void World::updatePopups(sf::Time dt)
    {
        // todo later combine into one?
        for (auto it = textPopups_.begin(); it != textPopups_.end(); )
        {
            it->durationRemaining -= dt;
            if (it->durationRemaining <= sf::Time::Zero)
            {
                it = textPopups_.erase(it); 
            }
            else
            {
                ++it;
            }
        }

        for (auto it = scorePopups_.begin(); it != scorePopups_.end(); )
        {
            it->durationRemaining -= dt;
            if (it->durationRemaining <= sf::Time::Zero)
            {
                it = scorePopups_.erase(it); 
            }
            else
            {
                ++it;
            }
        }
    }

    int World::score() const
    {
        return score_;
    }

    int World::lives() const
    {
        return lives_;
    }

    void World::notifyCutsceneFinished()
    {
        activeCutscene_ = Cutscenes::None;
        state_ = nextState_;
    }

    void World::notifyCutsceneStarted()
    {
        activeCutscene_ = requestedCutscene_;
        requestedCutscene_ = Cutscenes::None;
        state_ = WorldState::Cutscene;
    }


    Cutscenes World::requestedCutscene() const
    {
        return requestedCutscene_;
    }


    Cutscenes World::activeCutscene() const
    {
        return activeCutscene_;
    }

    void World::setBGM()
    {
        /*
        background music priority:
        1. ghostEaten and eyes returning
        2. frightened
        4. siren loop
        
        */
        if (anyGhostReturningHome())
        {
            gameAudio_.playMusic(MusicTrackId::Eyes);
        }
        else if (ghostDirector_.frightened())
        {
            gameAudio_.playMusic(MusicTrackId::Frightened);
        } 
        else if (dotsEaten_ < 16)
        {
            gameAudio_.playMusic(MusicTrackId::Siren0);
        }
        else if (dotsEaten_ < 81)
        {
            gameAudio_.playMusic(MusicTrackId::Siren1);
        }
        else if (dotsEaten_ < 145)
        {
            gameAudio_.playMusic(MusicTrackId::Siren2);
        }
        else if (dotsEaten_ < 209)
        {
            gameAudio_.playMusic(MusicTrackId::Siren3);
        }
        else
        {
            gameAudio_.playMusic(MusicTrackId::Siren4);
        }
    }

    bool World::anyGhostReturningHome() const
    {
        for (const Ghost& ghost : { std::ref(blinky_), std::ref(pinky_),
                      std::ref(inky_), std::ref(clyde_) })
        {
            if (ghost.state() == GhostState::EatenReturning)
            {
                return true;
            }
        }

        return false;
    }

     void World::newGame(sf::Time dt)
     {
        startNewGameTimer_ += dt;
        gameAudio_.playMusic(MusicTrackId::StartGame);
        updatePopups(dt);

        if (startNewGameTimer_ >= NEW_GAME_INTRO_SPAWN_CHARACTER_TIME)
        {
            blinky_.setVisible(true);
            pinky_.setVisible(true);
            inky_.setVisible(true);
            clyde_.setVisible(true);
            pacmanEntity_.setVisible(true);
        }

        if (startNewGameTimer_ >= NEW_GAME_INTRO)
        {
            startNewGameTimer_ = sf::Time::Zero;
            gameAudio_.stopMusic();
            state_ = WorldState::Playing;
            pacmanEntity_.setState(PacmanState::Normal);
        }
     }

    void World::setStartNewGame()
    {
        state_ = WorldState::NewGame;
        auto loc = maze_.tileToWorld(Maze::READY_POPUP_TILE);
        pacmanEntity_.setState(PacmanState::Circle);
        textPopups_.push_back({loc, NEW_GAME_INTRO_SPAWN_CHARACTER_TIME, TextColors::YELLOW, "Ready! "});
    }

    void World::died(sf::Time dt)
    {
        updatePopups(dt);

        if (diedTimer_ <= sf::Time::Zero)
        {
            pacmanEntity_.requestResetDiedAnimation();
            blinky_.setDirection(Dir::None);
            pinky_.setDirection(Dir::None);
            inky_.setDirection(Dir::None);
            clyde_.setDirection(Dir::None);
            pacmanEntity_.setDirection(Dir::None);
        }

        diedTimer_ += dt;

        if (diedTimer_ > DIED_ANIM_START_TIME)
        {
            blinky_.setVisible(false);
            pinky_.setVisible(false);
            inky_.setVisible(false);
            clyde_.setVisible(false);
            pacmanEntity_.setState(PacmanState::Dying);
            gameAudio_.playMusic(MusicTrackId::Died);
        }
        else
        {
            gameAudio_.stopMusic();
        }

        if (diedTimer_ > DIED_STATE_TIME)
        {
            diedTimer_ = sf::Time::Zero;
            //todo gameover if lives run out
            state_ = WorldState::RestartLevel;
        }

    }

    void World::resetEntities()
    {
            ghostDirector_.restartLevel();

            blinky_.setState(GhostState::Chase);
            blinky_.setHouseState(HouseState::Outside);
            blinky_.setPosition(maze_.tileToWorldOnBoundary(Maze::INFRONT_DOOR_LEFT), Maze::INFRONT_DOOR_LEFT);
            blinky_.setDirection(Dir::Left);
            blinky_.setVisible(true);

            pinky_.setState(GhostState::Chase);
            pinky_.setPosition(maze_.tileToWorldOnBoundary(Maze::HOUSE_CENTER), Maze::HOUSE_CENTER);
            pinky_.setDirection(Dir::Down);
            pinky_.setHouseState(HouseState::InHouse);
            pinky_.setVisible(true);
            
            inky_.setState(GhostState::Chase);
            inky_.setPosition(maze_.tileToWorldOnBoundary(Maze::HOUSE_LEFT), Maze::HOUSE_LEFT);
            inky_.setDirection(Dir::Up);
            inky_.setHouseState(HouseState::InHouse);
            inky_.setVisible(true);

            clyde_.setState(GhostState::Chase);
            clyde_.setPosition(maze_.tileToWorldOnBoundary(Maze::HOUSE_RIGHT), Maze::HOUSE_RIGHT);
            clyde_.setDirection(Dir::Up);
            clyde_.setHouseState(HouseState::InHouse);
            clyde_.setVisible(true);

            pacmanEntity_.reset();
            pacmanEntity_.setState(PacmanState::Circle);
            pacmanEntity_.setPosition(maze_.tileToWorldOnBoundary(Maze::PACMAN_SPAWN_POINT), Maze::PACMAN_SPAWN_POINT);
            pacmanEntity_.setDirection(Dir::Right);
    }


    void World::restartLevel(sf::Time dt)
    {
        updatePopups(dt);
        // reset positions only first time entering this state
        if (restartLevelTimer_ <= sf::Time::Zero)
        { 
            resetEntities();

            auto loc = maze_.tileToWorld(Maze::READY_POPUP_TILE);
            textPopups_.push_back({loc, RESTART_LEVEL_PAUSE_TIME, TextColors::YELLOW, "Ready!"});
        }

        restartLevelTimer_ += dt;
        if (restartLevelTimer_ >= RESTART_LEVEL_PAUSE_TIME)
        { 
            restartLevelTimer_ = sf::Time::Zero;
            pacmanEntity_.setState(PacmanState::Normal);
            state_ = WorldState::Playing;
        }

    }

    MazeDisplayMode World::mazeDisplayMode() const
    {
        return mazeDisplayMode_;
    }

    void World::levelCleared(sf::Time dt)
    {
        updatePopups(dt);

        if (levelClearedPhase1Timer_ == sf::Time::Zero)
        {
            pacmanEntity_.setState(PacmanState::Circle);
            gameAudio_.stopMusic();
        }

        levelClearedPhase1Timer_ += dt;

        if (levelClearedPhase1Timer_ > LEVEL_CLEARED_PHASE_1)
        {            
            if (levelClearedPhase2Timer_ == sf::Time::Zero)
            {
                mazeDisplayMode_ = MazeDisplayMode::NoDoorBlue;
                blinky_.setVisible(false);
                pinky_.setVisible(false);
                inky_.setVisible(false);
                clyde_.setVisible(false);
            }

            levelClearedPhase2Timer_ += dt;
            flashMazeTimer_ += dt;
            if (flashMazeTimer_ >= MAZE_FLASH_TIME)
            {
                flashMazeTimer_ -= MAZE_FLASH_TIME;
                if (mazeDisplayMode_ == MazeDisplayMode::NoDoorBlue)
                {
                    mazeDisplayMode_ = MazeDisplayMode::NoDoorWhite;
                }
                else
                {
                    mazeDisplayMode_ = MazeDisplayMode::NoDoorBlue;
                }
            }

        }

        if (levelClearedPhase2Timer_ > LEVEL_CLEARED_PHASE_2)
        {
            levelClearedPhase1Timer_ = sf::Time::Zero;
            levelClearedPhase2Timer_ = sf::Time::Zero;
            flashMazeTimer_ = sf::Time::Zero;
            pacmanEntity_.setState(PacmanState::Normal);
            advanceNextLevel();
            mazeDisplayMode_ = MazeDisplayMode::Normal;

            // just one cut scene for now
            if (level_ == 2)
            {
                nextState_ = WorldState::RestartLevel;
                requestedCutscene_ = Cutscenes::Intermission1;
                state_ = WorldState::Cutscene;
            }
            else
            {
                state_ = WorldState::RestartLevel;
            }

        }

    }

    void World::advanceNextLevel()
    {
        dotsEaten_ = 0;
        blinkElapsed_ = sf::Time::Zero;
        maze_.reset();
        // todo read in next levels
        // resetEntities();
    }

    Fruits World::spawnedFruit() const
    {
        return spawnedFruit_;
    }

    const sf::Vector2f& World::fruitPos() const
    {
        return fruitPos_;
    }
    
    Fruits World::getFruitForLevel() const
    {
        switch (level_)
        {
            case 1:
                return Fruits::Cherry;
            case 2:
                return Fruits::Strawberry;
            case 3:
            case 4:
                return Fruits::Peach;
            case 5:
            case 6:
                return Fruits::Apple;
            case 7:
            case 8:
                return Fruits::Grapes;
            case 9:
            case 10:
                return Fruits::Galaxian;
            case 11:
            case 12:
                return Fruits::Bell;
            default: // level 13+ always key
                return Fruits::Key;
        }
    }

    int World::getFruitScore() const
    {
        switch (spawnedFruit_)
        {
            case Fruits::Cherry:
                return 100;
            case Fruits::Strawberry:
                return 300;
            case Fruits::Peach:
                return 500;
            case Fruits::Apple:
                return 700;
            case Fruits::Grapes:
                return 1000;
            case Fruits::Galaxian:
                return 2000;
            case Fruits::Bell:
                return 3000;
            case Fruits::Key:
                return 5000;
            default:
                return 0;
        }
    }

    Scores World::getFruitScorePopup() const
    {
        switch (spawnedFruit_)
        {
            case Fruits::Cherry:
                return Scores::PinkScore100;
            case Fruits::Strawberry:
                return Scores::PinkScore300;
            case Fruits::Peach:
                return Scores::PinkScore500;
            case Fruits::Apple:
                return Scores::PinkScore700;
            case Fruits::Grapes:
                return Scores::PinkScore1000;
            case Fruits::Galaxian:
                return Scores::PinkScore2000;
            case Fruits::Bell:
                return Scores::PinkScore3000;
            case Fruits::Key:
                return Scores::PinkScore5000;
            default:
                return Scores::PinkScore100; // todo maybe make into optional but will never be called without fruit spawaned
        }
    }

    void World::handleFruit(sf::Time dt)
    {
        if (spawnedFruit_ == Fruits::None)
        {
            if (dotsEaten_ == FIRST_FRUIT_SPAWN_DOT_COUNT || dotsEaten_ == SECOND_FRUIT_SPAWN_DOT_COUNT)
            {
                spawnedFruit_ = getFruitForLevel();
                fruitTimer_ = sf::Time::Zero;
            }
        }
        else
        {
            fruitTimer_ += dt;
            if (fruitTimer_ >= FRUIT_SPAWN_TIME)
            {
                spawnedFruit_ = Fruits::None;
            }
        }

    }
}
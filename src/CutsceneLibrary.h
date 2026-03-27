#pragma once

#include "CutsceneBuilder.h"
#include "CutsceneActor.h"
#include "CutscenePlayer.h"
#include "AnimationLibrary.h"
#include "GameAudio.h"
#include "AtlasRegion.h"

namespace Pacman
{
    class CutsceneLibrary
    {
        public: 
            static void Intermission1(CutscenePlayer& player,
                                sf::Texture& atlas, GameAudio& gameAudio)
            {   
                player.reset();

                auto blinky = std::make_unique<GhostActor>(AnimationLibrary::MakeGhostAnimationPack(atlas, GameCharacters::Blinky));
                auto pacman = std::make_unique<PacmanActor>(AnimationLibrary::MakePacmanAnimationPack(atlas));
                GhostActor* blinkyPtr = blinky.get();
                PacmanActor* pacmanPtr = pacman.get();
                player.actors().push_back(std::move(blinky));
                player.actors().push_back(std::move(pacman));
                
                CutsceneBuilder script(player);

                script
                .setActorVisible(*blinkyPtr, true)
                .setActorVisible(*pacmanPtr, true)
                .playMusic(gameAudio, MusicTrackId::Intermission1)
                .setPos(*blinkyPtr, {260.f, 150.f})
                .setPos(*pacmanPtr, {230.f, 150.f})
                .run(*blinkyPtr, Dir::Left, 1.f)
                .run(*pacmanPtr, Dir::Left, .95f)
                .untilX(*pacmanPtr, -100.f)
                .setPacmanState(*pacmanPtr, PacmanState::Large)
                .setGhostState(*blinkyPtr, GhostState::Frightened)
                .setPos(*blinkyPtr, {-20.f, 150.f})
                .setPos(*pacmanPtr, {-100.f, 140.f})
                .run(*blinkyPtr, Dir::Right, .8f)
                .run(*pacmanPtr, Dir::Right, .95f)
                .untilX(*pacmanPtr, 310.f)
                .stopMusic(gameAudio);
            }

            static void Intermission2(CutscenePlayer& player,
                                sf::Texture& atlas, GameAudio& gameAudio)
            {
                player.reset();

                auto blinky = std::make_unique<GhostActor>(AnimationLibrary::MakeGhostAnimationPack(atlas, GameCharacters::Blinky));
                auto pacman = std::make_unique<PacmanActor>(AnimationLibrary::MakePacmanAnimationPack(atlas));
               
                player.props().reserve(7);
                player.props().push_back(Prop(atlas, Atlas::Nail));
                auto nail = &player.props().back();

                player.props().push_back(Prop(atlas, Atlas::BlinkyTear1));
                auto blinkyTear1 = &player.props().back();

                player.props().push_back(Prop(atlas, Atlas::BlinkyTear2));
                auto blinkyTear2 = &player.props().back();

                player.props().push_back(Prop(atlas, Atlas::BlinkyTear3));
                auto blinkyTear3 = &player.props().back();

                player.props().push_back(Prop(atlas, Atlas::BlinkyTear4));
                auto blinkyTear4 = &player.props().back();

                player.props().push_back(Prop(atlas, Atlas::BlinkyTear5));
                auto blinkyTear5 = &player.props().back();

                player.props().push_back(Prop(atlas, Atlas::BlinkyTear6));
                auto blinkyTear6 = &player.props().back();

                GhostActor* blinkyPtr = blinky.get();
                PacmanActor* pacmanPtr = pacman.get();
                player.actors().push_back(std::move(blinky));
                player.actors().push_back(std::move(pacman));
                
                CutsceneBuilder script(player);

                script
    
                .playMusic(gameAudio, MusicTrackId::Intermission1)
                .setPropVisible(*nail, true)
                // ghost sprite does not line up if at same x, y. see sprite sheet, ghost is 1px higher and 1px to the left if same x,y 
                .setPropPosition(*nail, {109.f, 149.f})
                .setPos(*blinkyPtr, {350.f, 150.f})
                .setPos(*pacmanPtr, {230.f, 150.f})
                .setActorVisible(*blinkyPtr, true)
                .setActorVisible(*pacmanPtr, true)
                .run(*blinkyPtr, Dir::Left, 1.f)
                .run(*pacmanPtr, Dir::Left, .95f)
                // begin nail caught sequencer
                .untilX(*blinkyPtr, 110.f)
                .run(*blinkyPtr, Dir::Left, .10f)
                .setPropPosition(*blinkyTear1, {109.f, 149.f})
                .setPropVisible(*blinkyTear1, true)
                .setPropVisible(*nail, false)
                .untilX(*blinkyPtr, 107.f)
                .setPropPosition(*blinkyTear2, {109.f, 149.f})
                .setPropVisible(*blinkyTear2, true)
                .setPropVisible(*blinkyTear1, false)
                .untilX(*blinkyPtr, 105.f)
                .setPropPosition(*blinkyTear3, {109.f, 149.f})
                .setPropVisible(*blinkyTear3, true)
                .setPropVisible(*blinkyTear2, false)
                .untilX(*blinkyPtr, 102.f)
                .freeze(*blinkyPtr) 
                .setPos(*blinkyPtr, {101.f, 150.f})
                .wait(sf::seconds(2.f))
                .setPropPosition(*blinkyTear4, {109.f, 149.f})
                .setPropVisible(*blinkyTear4, true)
                .setPropVisible(*blinkyTear3, false)
                .setPropPosition(*blinkyTear5, {100.f, 150.f})
                .setActorVisible(*blinkyPtr, false)
                .setPropVisible(*blinkyTear5, true)
                .wait(sf::seconds(1.f))
                .setPropPosition(*blinkyTear6, {100.f, 150.f})
                .setPropVisible(*blinkyTear6, true)
                .setPropVisible(*blinkyTear5, false)
                .wait(sf::seconds(2.f))
                .stopMusic(gameAudio);
            }

            static void IntroScreen(CutscenePlayer& player, TextureCache& cache)
            {
                sf::Texture& atlas = cache.get("atlas");
                player.props().reserve(10);

                player.props().push_back(Prop(cache.get("power_pellet"), Atlas::PowerPellet, {4.f, 4.f}));
                auto powerPellet = &player.props().back();

                player.props().push_back(Prop(cache.get("power_pellet"), Atlas::PowerPellet, {4.f, 4.f}));
                auto powerPellet2 = &player.props().back();

                player.props().push_back(Prop(cache.get("atlas"), Atlas::BlueScore200));
                auto score200 = &player.props().back();

                player.props().push_back(Prop(cache.get("atlas"), Atlas::BlueScore400));
                auto score400 = &player.props().back();

                player.props().push_back(Prop(cache.get("atlas"), Atlas::BlueScore800));
                auto score800 = &player.props().back();

                player.props().push_back(Prop(cache.get("atlas"), Atlas::BlueScore1600));
                auto score1600 = &player.props().back();


                auto blinky = std::make_unique<GhostActor>(AnimationLibrary::MakeGhostAnimationPack(atlas, GameCharacters::Blinky));
                auto pinky = std::make_unique<GhostActor>(AnimationLibrary::MakeGhostAnimationPack(atlas, GameCharacters::Pinky));
                auto inky = std::make_unique<GhostActor>(AnimationLibrary::MakeGhostAnimationPack(atlas, GameCharacters::Inky));
                auto clyde = std::make_unique<GhostActor>(AnimationLibrary::MakeGhostAnimationPack(atlas, GameCharacters::Clyde));
                auto pacman = std::make_unique<PacmanActor>(AnimationLibrary::MakePacmanAnimationPack(atlas));
                
                GhostActor* blinkyPtr = blinky.get();
                GhostActor* pinkyPtr = pinky.get();
                GhostActor* inkyPtr = inky.get();
                GhostActor* clydePtr = clyde.get();
                PacmanActor* pacmanPtr = pacman.get();
                player.actors().push_back(std::move(blinky));
                player.actors().push_back(std::move(pinky));
                player.actors().push_back(std::move(inky));
                player.actors().push_back(std::move(clyde));
                player.actors().push_back(std::move(pacman));

                CutsceneBuilder script(player);
                float blinkyStartPos = 260.f;
                script
                .setPropPosition(*powerPellet, {84.f, 211.f})
                .blinkingProp(*powerPellet, sf::milliseconds(150))
                .setPropPosition(*powerPellet2, {40.f, 170.f})
                .blinkingProp(*powerPellet2, sf::milliseconds(150))
                .setPos(*blinkyPtr, {blinkyStartPos, 170.f})
                .setPos(*pinkyPtr, {blinkyStartPos + 17.f, 170.f})
                .setPos(*inkyPtr, {blinkyStartPos + 17.f*2, 170.f})
                .setPos(*clydePtr, {blinkyStartPos + 17.f*3, 170.f})
                .setPos(*pacmanPtr, {230.f, 170.f})
                .setActorVisible(*blinkyPtr, true)
                .setActorVisible(*pinkyPtr, true)
                .setActorVisible(*inkyPtr, true)
                .setActorVisible(*clydePtr, true)
                .setActorVisible(*pacmanPtr, true)
                .run(*blinkyPtr, Dir::Left, 1.f) 
                .run(*pinkyPtr, Dir::Left, 1.f)
                .run(*inkyPtr, Dir::Left, 1.f)
                .run(*clydePtr, Dir::Left, 1.f)
                .run(*pacmanPtr, Dir::Left, .95f)
                .untilX(*pacmanPtr, 40.f)
                .setCutsceneStepEnabled(player.backgroundSteps().back(), false)
                .setPropVisible(*powerPellet2, false)
                .setGhostState(*blinkyPtr, GhostState::Frightened)
                .setGhostState(*pinkyPtr, GhostState::Frightened)
                .setGhostState(*inkyPtr, GhostState::Frightened)
                .setGhostState(*clydePtr, GhostState::Frightened)
                .run(*blinkyPtr, Dir::Right, .5f) 
                .run(*pinkyPtr, Dir::Right, .5f)
                .run(*inkyPtr, Dir::Right, .5f)
                .run(*clydePtr, Dir::Right, .5f)
                .run(*pacmanPtr, Dir::Right, .95f)
                // first ghost eaten
                .untilX(*pacmanPtr, 60.f)
                .freeze(*blinkyPtr) 
                .freeze(*pinkyPtr) 
                .freeze(*inkyPtr) 
                .freeze(*clydePtr) 
                .freeze(*pacmanPtr) 
                .setActorVisible(*blinkyPtr, false)
                .setActorVisible(*pacmanPtr, false)
                .setPropPosition(*score200, {70.f, 170.f})
                .setPropVisible(*score200, true)
                .wait(sf::seconds(1.f))
                .setPropVisible(*score200, false)
                .setActorVisible(*pacmanPtr, true)
                .freeze(*pinkyPtr, false) 
                .freeze(*inkyPtr, false) 
                .freeze(*clydePtr, false) 
                .freeze(*pacmanPtr, false)
                // second ghost eaten 
                .untilX(*pacmanPtr, 95.f)
                .freeze(*pinkyPtr) 
                .freeze(*inkyPtr) 
                .freeze(*clydePtr) 
                .freeze(*pacmanPtr) 
                .setActorVisible(*pinkyPtr, false)
                .setActorVisible(*pacmanPtr, false)
                .setPropPosition(*score400, {105.f, 170.f})
                .setPropVisible(*score400, true)
                .wait(sf::seconds(1.f))
                .setPropVisible(*score400, false)
                .setActorVisible(*pacmanPtr, true)
                .freeze(*inkyPtr, false) 
                .freeze(*clydePtr, false) 
                .freeze(*pacmanPtr, false)
                // thrid ghost eaten
                .untilX(*pacmanPtr, 130.f)
                .freeze(*inkyPtr) 
                .freeze(*clydePtr) 
                .freeze(*pacmanPtr) 
                .setActorVisible(*inkyPtr, false)
                .setActorVisible(*pacmanPtr, false)
                .setPropPosition(*score800, {140.f, 170.f})
                .setPropVisible(*score800, true)
                .wait(sf::seconds(1.f))
                .setPropVisible(*score800, false)
                .setActorVisible(*pacmanPtr, true)
                .freeze(*clydePtr, false) 
                .freeze(*pacmanPtr, false)
                //fourth ghost
                .untilX(*pacmanPtr, 170.f)
                .freeze(*clydePtr) 
                .freeze(*pacmanPtr) 
                .setActorVisible(*clydePtr, false)
                .setActorVisible(*pacmanPtr, false)
                .setPropPosition(*score1600, {180.f, 170.f})
                .setPropVisible(*score1600, true)
                .wait(sf::seconds(1.f))
                .setPropVisible(*score1600, false)
                .setActorVisible(*pacmanPtr, true)
                .freeze(*pacmanPtr, false)
                .untilX(*pacmanPtr, 300.f)
                .freeze(*pacmanPtr, false)
                .keepCutsceneAlive();

            }
    };
}
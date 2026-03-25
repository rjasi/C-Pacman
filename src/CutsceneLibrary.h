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
                .untilX(*blinkyPtr, 101.f)
                .run(*blinkyPtr, Dir::Left, 0.f)
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
    };
}
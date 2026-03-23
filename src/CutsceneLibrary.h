#pragma once

#include "CutsceneBuilder.h"
#include "CutsceneActor.h"
#include "CutscenePlayer.h"
#include "AnimationLibrary.h"
#include "GameAudio.h"

namespace Pacman
{
    class CutsceneLibrary
    {
        public: 
            static void Intermission1(CutscenePlayer& player,
                                sf::Texture& atlas, GameAudio& gameAudio)
            {

                // auto pacman = std::make_unique<PacmanActor>(
                //     anims.makePacman(atlas));

                auto blinky = std::make_unique<GhostActor>(AnimationLibrary::MakeGhostAnimationPack(atlas, GameCharacters::Blinky));
                auto pacman = std::make_unique<PacmanActor>(AnimationLibrary::MakePacmanAnimationPack(atlas));

                // PacmanCinematicActor* pacmanPtr = pacman.get();
                GhostActor* blinkyPtr = blinky.get();
                PacmanActor* pacmanPtr = pacman.get();
                // player.actors().push_back(std::move(pacman));
                player.actors().push_back(std::move(blinky));
                player.actors().push_back(std::move(pacman));

                CutsceneBuilder script(player);

                script
                .setPos(*blinkyPtr, {260.f, 150.f})
                .setPos(*pacmanPtr, {230.f, 150.f})
                .run(*blinkyPtr, Dir::Left, 1.f)
                .run(*pacmanPtr, Dir::Left, .95f)
                .playMusic(gameAudio, MusicTrackId::Intermission1)
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
    };
}
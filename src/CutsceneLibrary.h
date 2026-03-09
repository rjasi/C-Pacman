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

                // PacmanCinematicActor* pacmanPtr = pacman.get();
                GhostActor* blinkyPtr = blinky.get();

                // player.actors().push_back(std::move(pacman));
                player.actors().push_back(std::move(blinky));

                CutsceneBuilder script(player);

                script
                .setPos(*blinkyPtr, {12.f, 12.f})
                .playMusic(gameAudio, MusicTrackId::Intermission1)
                .wait(sf::seconds(7.0f))
                .stopMusic(gameAudio);


                // player.steps().push_back({
                //     .onEnter = [pacmanPtr] {
                //         pacmanPtr->setPosition({-16.f, 140.f});
                //         pacmanPtr->setDirection(Dir::Right);
                //         pacmanPtr->setVelocity({80.f, 0.f});
                //     }
                // });
            }
    };
}
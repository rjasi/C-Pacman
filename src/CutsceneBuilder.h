#pragma once

#include "CutscenePlayer.h"
#include "CutsceneStep.h"
#include "GameAudio.h"
#include "MusicTrackId.h"
#include "PacmanState.h"
#include "GhostState.h"


namespace Pacman
{
    // takes in a player and sets in steps

    class CutsceneBuilder
    {

        public:
            CutsceneBuilder() = delete;
            explicit CutsceneBuilder(CutscenePlayer& player);

            CutsceneBuilder& setPos(CutsceneActor& actor, sf::Vector2f pos);
            CutsceneBuilder& show(std::size_t actor, bool visible = true);
            CutsceneBuilder& run(CutsceneActor& actor, Dir dir, float speed);
            CutsceneBuilder& freeze(CutsceneActor& actor, bool freeze = true);
            CutsceneBuilder& wait(sf::Time duration);
            CutsceneBuilder& untilX(CutsceneActor& actor, float x);
            CutsceneBuilder& setPacmanState(PacmanActor& actor, PacmanState state);
            CutsceneBuilder& setGhostState(GhostActor& actor, GhostState state);
            CutsceneBuilder& playMusic(GameAudio& audio, MusicTrackId trackId);
            CutsceneBuilder& stopMusic(GameAudio& audio);
            CutsceneBuilder& setPropVisible(Prop& prop, bool visible);
            CutsceneBuilder& setActorVisible(CutsceneActor& actor, bool visible);
            CutsceneBuilder& setPropPosition(Prop& prop, sf::Vector2f pos);
            CutsceneBuilder& blinkingProp(Prop& prop, sf::Time flashTime);
            CutsceneBuilder& setCutsceneStepEnabled(CutsceneStep& step, bool enabled);
            CutsceneBuilder& keepCutsceneAlive();
        private:
            CutscenePlayer& player_;

    };
}
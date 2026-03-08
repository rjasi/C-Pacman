#pragma once

#include "CutscenePlayer.h"
#include "CutsceneStep.h"


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
            CutsceneBuilder& run(std::size_t actor, Dir dir, float speed);
            CutsceneBuilder& stop(std::size_t actor);
            CutsceneBuilder& wait(sf::Time duration);
            CutsceneBuilder& untilX(std::size_t actor, float x);
            CutsceneBuilder& untilXLess(std::size_t actor, float x);

        private:
            void updateAllActors(sf::Time dt);
            CutscenePlayer& player_;

    };
}
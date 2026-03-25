#pragma once

#include "CutsceneActor.h"
#include "CutsceneStep.h"

#include <SFML/Graphics.hpp>

/*
pacman cutscenes consist of sprites moving in some direction while animations playing 

cutscene idea: 
CutsceneActor stores
 - speed 
 - direction
 - Animation clips

Cutscene player
 - takes in sf::Rendertarget and draws based on cutscene actor data 


*/

namespace Pacman
{
    class CutscenePlayer
    {
        public:
            void update(sf::Time dt);
            void render(sf::RenderTarget& window);
            void start();
            void reset();
            bool active() const;
            bool finished() const;

            std::vector<std::unique_ptr<CutsceneActor>>& actors();

            std::vector<Prop>& props();
            std::vector<CutsceneStep>& steps();

        private:
            std::vector<std::unique_ptr<CutsceneActor>> actors_;
            std::vector<Prop> props_;

            std::vector<CutsceneStep> steps_;

            bool active_ = false;
            std::size_t currentStep_ = 0;
            bool entered_ = false;
            sf::Time stepTime_ = sf::Time::Zero;

    };
}
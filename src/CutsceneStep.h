#pragma once

#include <functional>

namespace Pacman
{
    /* 
        alternatively this can be done via inheritance 
        class CutsceneStep
            {
                public:
                    virtual void onEnter() = 0;
                    virtual void(sf::Time) update = 0;
                    virtual bool() done = 0;
                    void() onExit = 0;
                    virtual ~CutsceneStep(){}
            };

        but would require heap allocations for runtime polymorhpism
        
    
    */
    class CutsceneStep
    {
        public:
            bool enabled = true;
            std::function<void()> onEnter = [] {};
            std::function<void(sf::Time)> update = [](sf::Time) {};
            std::function<bool(sf::Time)> done = [](sf::Time) { return true; };
            std::function<void()> onExit = [] {};
    };

}
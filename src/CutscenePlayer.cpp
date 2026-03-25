#include "CutscenePlayer.h"

#include <iostream>

namespace Pacman
{
    std::vector<std::unique_ptr<CutsceneActor>>& CutscenePlayer::actors() 
    { 
        return actors_; 
    }
    
    std::vector<Prop>& CutscenePlayer::props()
    {
        return props_;
    }

    std::vector<CutsceneStep>& CutscenePlayer::steps() 
    { 
        return steps_;
    }

    bool CutscenePlayer::finished() const
    {
        return active_ && currentStep_ >= steps_.size();
    }

    bool CutscenePlayer::active() const
    {
        return active_;
    }


    void CutscenePlayer::start()
    {
        active_ = true;
        currentStep_ = 0;
        stepTime_ = sf::Time::Zero;
        entered_ = false;
    } 

    void CutscenePlayer::reset()
    {
        actors_.clear();
        steps_.clear();
        currentStep_ = 0;
        stepTime_ = sf::Time::Zero;
        entered_ = false;
        active_ = false;
    }

    void CutscenePlayer::render(sf::RenderTarget& window)
    {
   
        for (const Prop& prop : props_)
        {
            if (prop.visible())
            {
                window.draw(prop);
            }
        }

        for (std::unique_ptr<CutsceneActor>& actor: actors_)
        {
            actor->render(window);
        }
    }

    void CutscenePlayer::update(sf::Time dt)
    {
        if (steps_.empty() || !active_ || finished())
        {
            return;
        }

        for (std::unique_ptr<CutsceneActor>& actor : actors_)
        {
            actor->update(dt);
        }

        auto& step = steps_[currentStep_];

        if (!entered_)
        {
            entered_ = true;
            stepTime_ = sf::Time::Zero;

            if (step.onEnter)
            {
                step.onEnter();
            }
        }

        stepTime_ += dt;

        if (step.done && step.done(stepTime_))
        {
            currentStep_++;
            entered_ = false;
        }
    }
}
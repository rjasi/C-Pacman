#include "CutsceneBuilder.h"
#include "CutsceneActor.h"

namespace Pacman
{

    CutsceneBuilder::CutsceneBuilder(CutscenePlayer& player)
    : player_(player)
    {

    }

    CutsceneBuilder& CutsceneBuilder::setPos(CutsceneActor& actor, sf::Vector2f pos)
    {
        player_.steps().push_back(
        {
            .onEnter = [a = &actor, pos] 
            {
                a->setPosition(pos);
            }
        });
        return *this;
    }

    CutsceneBuilder& CutsceneBuilder::freeze(CutsceneActor& actor, bool freeze)
    {
         player_.steps().push_back(
        {
            .onEnter = [a = &actor, freeze] 
            {
                a->freeze(freeze);
            }
        });

        return *this;
    }

    CutsceneBuilder& CutsceneBuilder::setActorVisible(CutsceneActor& actor, bool visible)
    {
        player_.steps().push_back(
        {
            .onEnter = [a = &actor, visible] 
            {
                a->setVisible(visible);
            }
        });

        return *this;
    }

    CutsceneBuilder& CutsceneBuilder::run(CutsceneActor& actor, Dir dir, float speed)
    {
        player_.steps().push_back(
        {
            .onEnter = [a = &actor, speed, dir] 
            {
                a->setDirection(dir);
                a->setSpeed(speed);
            }
        });

        return *this;
    }

    CutsceneBuilder& CutsceneBuilder::untilX(CutsceneActor& actor, float x)
    {
        player_.steps().push_back(
        {
            .done = [a = &actor, x](sf::Time stepTime) 
            {
                switch (a->direction())
                {
                    case Dir::Left:
                        return a->position().x <= x;
                    case Dir::Right:
                        return a->position().x >= x;
                    default:
                        return true;
                }
            }
        });
        return *this;
    }

    CutsceneBuilder& CutsceneBuilder::setPacmanState(PacmanActor& actor, PacmanState state)
    {
        player_.steps().push_back(
        {
            .onEnter = [a = &actor, state] 
            {
                a->setState(state);
            }
        });

        return *this;
    }

    CutsceneBuilder& CutsceneBuilder::setGhostState(GhostActor& actor, GhostState state)
    {
        player_.steps().push_back(
        {
            .onEnter = [a = &actor, state] 
            {
                a->setState(state);
            }
        });

        return *this;
    }

    CutsceneBuilder& CutsceneBuilder::wait(sf::Time duration)
    {
        player_.steps().push_back(
        {
            .done = [duration](sf::Time stepTime) 
            {
                return stepTime >= duration;
            }
        });
        return *this;
    }

    CutsceneBuilder& CutsceneBuilder::setPropPosition(Prop& prop, sf::Vector2f pos)
    {
        player_.steps().push_back(
        {
            .onEnter = [p = &prop, pos] 
            {
                p->setPosition(pos);
            }
        });

        return *this;

    }

    CutsceneBuilder& CutsceneBuilder::blinkingProp(Prop& prop, sf::Time blinkTIme)
    {
        sf::Time time;
        player_.backgroundSteps().push_back(
        {
            .update = [p = &prop, blinkElapsed = time, blinkTIme](sf::Time stepTime) mutable
            {
                blinkElapsed += stepTime;
                if (blinkElapsed >= blinkTIme)
                {
                    blinkElapsed -= blinkTIme;
                    p->setVisible(!p->visible());
                }
            }
        });

        return *this;
    }

    CutsceneBuilder& CutsceneBuilder::keepCutsceneAlive()
    {
        player_.steps().push_back(
        {
            .done = [](sf::Time stepTime) 
            {
                return false;
            }
        });

        return *this;
    }

    CutsceneBuilder& CutsceneBuilder::setCutsceneStepEnabled(CutsceneStep& step, bool enabled)
    {
        player_.steps().push_back(
        {
            .onEnter = [s = &step, enabled] 
            {
                s->enabled = enabled;
            }
        });
        
        return *this;
    }

    


    CutsceneBuilder& CutsceneBuilder::setPropVisible(Prop& prop, bool visible)
    {
        player_.steps().push_back(
        {
            .onEnter = [p = &prop, visible] 
            {
                p->setVisible(visible);
            }
        });
        
        return *this;
    }

    CutsceneBuilder& CutsceneBuilder::playMusic(GameAudio& audio, MusicTrackId trackId)
    {
        player_.steps().push_back(
        {
            .onEnter = [a = &audio, trackId] 
            {
                a->playMusic(trackId);
            }
        });
        
        return *this;
    }

    CutsceneBuilder& CutsceneBuilder::stopMusic(GameAudio& audio)
    {
        player_.steps().push_back(
        {
            .onEnter = [a = &audio] 
            {
                a->stopMusic();
            }
        });

        return *this;
    }


}
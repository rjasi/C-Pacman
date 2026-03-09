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
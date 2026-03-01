#include "SfxMixer.h"

#include <iostream>

namespace Pacman
{
    SfxMixer::SfxMixer(const AudioBank& audioBank)
    : audioBank_(audioBank)
    {
        sounds_.reserve(Channels);
        for (std::size_t i = 0; i < Channels; i++)
        {
            sounds_.emplace_back(audioBank.silence()); 
        }
    }

    void SfxMixer::play(SfxId sfxId, float volume)
    {
        sf::Sound& channel = getChannel();
        channel.stop();
        channel.setBuffer(audioBank_.get(sfxId));
        channel.setVolume(volume);
        channel.play();        
    }

    sf::Sound& SfxMixer::getChannel()
    {
        for (sf::Sound& s : sounds_)
        {
            if (s.getStatus() == sf::Sound::Status::Stopped)
            {
                return s;
            }
        }
        sf::Sound& s = sounds_[stealIndex_];
        stealIndex_ = (stealIndex_ + 1) % Channels;

        return s;
    }

}
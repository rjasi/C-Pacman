#include "AudioBank.h"
#include "EnumToIndex.h"
#include <iostream>

namespace Pacman
{
    AudioBank::AudioBank()
    {
        //todo throw exception on not load
        bool succcess = buffers_[EnumHelper::toIndex(SfxId::Waka1)].loadFromFile("assets/sound/waka1.wav");
        if (!succcess)
        {
            std::cerr << "Could not load sound\n";
        }

        succcess = buffers_[EnumHelper::toIndex(SfxId::Waka2)].loadFromFile("assets/sound/waka2.wav");
        if (!succcess)
        {
            std::cerr << "Could not load sound\n";
        }

        std::vector<std::int16_t> silence(44100, 0);

        std::vector<sf::SoundChannel> channels = {sf::SoundChannel::Mono};
        silentBuffer_.loadFromSamples
        (
            silence.data(),
            silence.size(),
            1,
            44100,
            channels
        );
    }

    const sf::SoundBuffer& AudioBank::get(SfxId sfxid) const
    {
        return buffers_[EnumHelper::toIndex(sfxid)];
    }

    const sf::SoundBuffer& AudioBank::silence() const
    {
        return silentBuffer_;
    }
}
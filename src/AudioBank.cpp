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

        succcess = buffers_[EnumHelper::toIndex(SfxId::EatGhost)].loadFromFile("assets/sound/eat_ghost.wav");
        if (!succcess)
        {
            std::cerr << "Could not load sound\n";
        }

        succcess = buffers_[EnumHelper::toIndex(SfxId::EatFruit)].loadFromFile("assets/sound/eat_fruit.wav");
        if (!succcess)
        {
            std::cerr << "Could not load sound\n";
        }

        succcess = buffers_[EnumHelper::toIndex(SfxId::Credit)].loadFromFile("assets/sound/credit.wav");
        if (!succcess)
        {
            std::cerr << "Could not load sound\n";
        }

        succcess = buffers_[EnumHelper::toIndex(SfxId::Extend)].loadFromFile("assets/sound/extend.wav");
        if (!succcess)
        {
            std::cerr << "Could not load sound\n";
        }

        std::vector<std::int16_t> silence(44100, 0);

        std::vector<sf::SoundChannel> channels = {sf::SoundChannel::Mono};
        succcess = silentBuffer_.loadFromSamples
        (
            silence.data(),
            silence.size(),
            1,
            44100,
            channels
        );

        if (!succcess)
        {
            std::cerr << "Could not load sound\n";
        }
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
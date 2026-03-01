#pragma once 

#include <AudioBank.h>
#include <SfxId.h>

#include <vector>

#include <SFML/Audio.hpp>


namespace Pacman
{
    class SfxMixer
    {
        public:
            static constexpr std::size_t Channels = 32;

            SfxMixer(const AudioBank& audioBank);
            void play(SfxId sfxId, float volume = 100.f);
        
        private:
            void cleanup();
            sf::Sound& getChannel();

            const AudioBank& audioBank_;
            std::vector<sf::Sound> sounds_;
            int stealIndex_ = 0;

    };

}
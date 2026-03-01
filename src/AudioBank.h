#pragma once

#include "SfxId.h"

#include <array>

#include <SFML/Audio.hpp>

namespace Pacman
{
    class AudioBank
    {
        public:
            AudioBank();
            const sf::SoundBuffer& get(SfxId) const;
            const sf::SoundBuffer& silence() const;

        private:
            std::array<sf::SoundBuffer, static_cast<size_t>(SfxId::Count)> buffers_;
            sf::SoundBuffer silentBuffer_;
    };
}

#pragma once

#include "SfxMixer.h"
#include "AudioBank.h"
#include "SfxId.h"

namespace Pacman
{
    class GameAudio
    {
        public:
            GameAudio();
            void playSfx(SfxId sfxId);
        private:
            AudioBank audioBank_;
            SfxMixer  sfxMixer_;
            // MusicPlayer music_;
            float masterVolume_ = 1.f;
            float sfxVolume_    = 100.f;
    };
}
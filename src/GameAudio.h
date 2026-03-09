#pragma once

#include "SfxMixer.h"
#include "AudioBank.h"
#include "SfxId.h"
#include "MusicPlayer.h"
#include "MusicTrackId.h"

namespace Pacman
{
    class GameAudio
    {
        public:
            GameAudio();
            void playSfx(SfxId sfxId);
            void playMusic(MusicTrackId trackId);
            void stopMusic();
            void pauseMusic();

        private:
            AudioBank audioBank_;
            SfxMixer  sfxMixer_;
            MusicPlayer musicPlayer_;
            float masterVolume_ = 1.f;
            float sfxVolume_    = 100.f;
    };
}
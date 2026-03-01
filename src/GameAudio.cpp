#include "GameAudio.h"


namespace Pacman
{
    GameAudio::GameAudio()
    : sfxMixer_(audioBank_)
    {

    }

    void GameAudio::playSfx(SfxId sfxId)
    {
        sfxMixer_.play(sfxId, sfxVolume_ * masterVolume_);
    }

}
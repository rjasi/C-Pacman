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

    void GameAudio::playMusic(MusicTrackId trackId)
    {
        musicPlayer_.play(trackId);
    }

    void GameAudio::stopMusic()
    {
        musicPlayer_.stop();
    }

    void GameAudio::pauseMusic()
    {
        musicPlayer_.pause();
    }

    void GameAudio::resumeMusic()
    {
        musicPlayer_.resume();
    }

}
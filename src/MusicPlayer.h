#pragma once

#include "EnumToIndex.h"
#include "MusicTrackId.h"

#include <SFML/Audio.hpp>
#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <iostream>



namespace Pacman
{

    class MusicDef
    {
        public:
            const char* path;
            bool loop;
    };

    class MusicPlayer
    {
        public:
            void play(MusicTrackId id, float volume = 100.f)
            {
                if (current_.has_value() && current_.value() == id)
                {
                    resume();
                    return;
                }

                stop();

                const auto& def = MUSIC_TABLE[static_cast<std::size_t>(id)];

                if (!music_.openFromFile(def.path))
                {
                    throw std::runtime_error("Failed to open music file");
                }

                music_.setLooping(def.loop);
                music_.setVolume(volume);
                music_.play();

                current_ = id;
            }

            void stop()
            {
                current_.reset();
                music_.stop();
            }

            void pause()
            {
                music_.pause();
            }

            void resume()
            {
                if (music_.getStatus() == sf::SoundSource::Status::Paused)
                {
                    music_.play();
                }
            }

            [[nodiscard]] std::optional<MusicTrackId> current() const
            {
                return current_;
            }

        private:
            sf::Music music_;
            std::optional<MusicTrackId> current_;

            static constexpr std::array<MusicDef, static_cast<std::size_t>(MusicTrackId::Count)> MUSIC_TABLE
            {
                MusicDef{"assets/sound/intermission.wav", true},
                MusicDef{"assets/sound/frightened.wav", true},
                MusicDef{"assets/sound/eyes.wav", true},
                MusicDef{"assets/sound/siren0.wav", true},
                MusicDef{"assets/sound/siren1.wav", true},
                MusicDef{"assets/sound/siren2.wav", true},
                MusicDef{"assets/sound/siren3.wav", true},
                MusicDef{"assets/sound/siren4.wav", true},
                MusicDef{"assets/sound/start.wav", false},
                MusicDef{"assets/sound/died.flac", false},
            };

                    

    };
}

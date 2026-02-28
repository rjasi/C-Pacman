// #include <SFML/Audio.hpp>
// #include <vector>
// #include <cmath>
// #include <cstdint>


// namespace Pacman
// {
//     class WakaSynth
// {
// public:
//     std::vector<std::int16_t> makeWakaTone(
//         float frequency,
//         float durationSec,
//         unsigned sampleRate = 44100)
//     {
//         const std::size_t sampleCount =
//             static_cast<std::size_t>(durationSec * sampleRate);

//         std::vector<std::int16_t> samples(sampleCount);

//         constexpr float twoPi = 6.28318530718f;

//         for (std::size_t i = 0; i < sampleCount; ++i)
//         {
//             float t = static_cast<float>(i) / sampleRate;

//             // --- envelope (fast attack + short release)
//             float attack = 0.003f;
//             float release = 0.015f;
//             float env = 1.f;

//             if (t < attack)
//                 env = t / attack;

//             float remaining = durationSec - t;
//             if (remaining < release)
//                 env = std::min(env, remaining / release);

//             // --- square-ish wave (arcade feel)
//             float s = std::sin(twoPi * frequency * t);
//             float square = (s >= 0.f) ? 1.f : -1.f;

//             float value = square * env * 0.35f; // gain

//             samples[i] = static_cast<std::int16_t>(value * 32767.f);
//         }

//         return samples;
//     }


//     void init()
//     {
//         constexpr float duration = 0.045f;

//         auto a = makeWakaTone(520.f, duration);
//         auto b = makeWakaTone(440.f, duration);

//         if (!bufferA_.loadFromSamples(a.data(), static_cast<std::uint64_t>(a.size()), 1, 
//             44100, { sf::SoundChannel::Mono }))
//         {
//             throw std::runtime_error("waka A failed");
//         }




//         if (!bufferB_.loadFromSamples(b.data(), static_cast<std::uint64_t>(b.size()), 1, 
//             44100, { sf::SoundChannel::Mono }))
//         {
//             throw std::runtime_error("waka B failed");
//         }

//         poolA_.setBuffer(bufferA_);
//         poolB_.setBuffer(bufferB_);
        
//     }

//     void pelletEaten()
//     {
//         if (flip_)
//             poolA_.play(75.f);
//         else
//             poolB_.play(75.f);

//         flip_ = !flip_;
//     }

// private:
//     // small pool to prevent clipping when pellets eaten quickly
//     class Pool {
// public:
//     explicit Pool(std::size_t n = 6) : capacity_(n) {}

//     void setBuffer(const sf::SoundBuffer& b)
//     {
//         sounds_.clear();
//         sounds_.reserve(capacity_);
//         for (std::size_t i = 0; i < capacity_; ++i)
//             sounds_.emplace_back(b); // <-- SFML 3: construct with buffer
//     }

//     void play(float volume)
//     {
//         if (sounds_.empty()) return;

//         for (auto& s : sounds_) {
//             if (s.getStatus() != sf::Sound::Status::Playing) {
//                 s.setVolume(volume);
//                 s.play();
//                 return;
//             }
//         }

//         // steal first if all busy
//         sounds_[0].stop();
//         sounds_[0].setVolume(volume);
//         sounds_[0].play();
//     }

// private:
//     std::size_t capacity_{};
//     std::vector<sf::Sound> sounds_;
// };

// private:
//     bool flip_ = false;

//     sf::SoundBuffer bufferA_;
//     sf::SoundBuffer bufferB_;

//     Pool poolA_{6};
//     Pool poolB_{6};
// };
// }
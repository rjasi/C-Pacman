#pragma once
#include <SFML/Audio.hpp>
#include <cstdint>
#include <vector>
#include <mutex>
#include <optional>
#include <cmath>
#include <algorithm>



namespace Pacman
{
    enum class Wave 
    {
        Sine,
        Square,
        Triangle,
        Saw,
        WsgApprox
    };

    class SfxSpec 
    {
        public:
            Wave wave{};
            float startHz{};
            float endHz{};          // sweep; set equal to startHz for none
            float durationSec{0.06f};
            float attackSec{0.002f}; // how quickly sound goes from silent to max vol
            float releaseSec{0.020f}; // how quickly to fade sound outs
            float gain{0.35f};      // 0..1 volume
    };

    struct AmbientSpec 
    {
        public:
            Wave carrier{};
            float baseHz{};
            float gain{0.18f};

            // LFO frequency modulation
            Wave lfoWave{Wave::Sine};
            float lfoHz{1.0f};
            float lfoDepthHz{50.0f}; // +/- Hz
    };

    // track where we are in a sound wave 
    class Voice
    {
        public:
            // waveform + gain
            Wave wave{};
            float gain{0.f};

            // oscillator phase [0,1)
            double phase{0.0};

            // for SFX sweep
            bool infinite{false};
            std::uint64_t ageFrames{0};
            std::uint64_t durFrames{0};
            std::uint64_t attackFrames{1};
            std::uint64_t releaseFrames{1};
            float startHz{0.f};
            float endHz{0.f};

            // LFO (ambient)
            Wave lfoWave{Wave::Sine};
            float lfoHz{0.f};
            float lfoDepthHz{0.f};
            double lfoPhase{0.0};

            static Voice makeSfx(const SfxSpec& s, unsigned sampleRate) 
            {
                Voice v;
                v.wave = s.wave;
                v.gain = s.gain;
                v.infinite = false;
                v.ageFrames = 0;
                v.durFrames = std::max<std::uint64_t>(1, (std::uint64_t)std::llround(s.durationSec * sampleRate));
                v.attackFrames = std::max<std::uint64_t>(1, (std::uint64_t)std::llround(s.attackSec * sampleRate));
                v.releaseFrames = std::max<std::uint64_t>(1, (std::uint64_t)std::llround(s.releaseSec * sampleRate));
                v.startHz = s.startHz;
                v.endHz = s.endHz;
                return v;
            }

        static Voice makeAmbient(const AmbientSpec& a) 
        {
            Voice v;
            v.wave = a.carrier;
            v.gain = a.gain;
            v.infinite = true;
            v.startHz = a.baseHz;
            v.endHz = a.baseHz;
            v.lfoWave = a.lfoWave;
            v.lfoHz = a.lfoHz;
            v.lfoDepthHz = a.lfoDepthHz;
            return v;
        }


        bool finished() const;

        // control how loud sound is at moment
        float envelope() const;
        
    };

    class SynthStream final : public sf::SoundStream 
    {
        public:
            // linear interpolation
            static float lerp(float a, float b, float t);

            explicit SynthStream(unsigned sampleRate = 44100);
            void start();

            //public apis 
            void playSfx(const SfxSpec& s);

        private:
            // SFML Sound stream specific functions
            bool onGetData(Chunk& data) override;
            void onSeek(sf::Time) override {} // empty do nothing
        
            static float osc(Wave w, double phase01);
            float nextSample(Voice& v);

            unsigned sampleRate_;
            static constexpr std::size_t chunkFrames_ = 1024;
            std::vector<std::int16_t> samples_;

            std::mutex mtx_;
            std::vector<Voice> sfx_;
            std::optional<Voice> ambient_;
    };

    class SynthLibrary
    {
        public:
            static SfxSpec Waka1() 
            {
                return {Wave::WsgApprox, 258.f, 287.f, 0.067f, 0.002f, 0.020f, 0.35f };
            }
    };

}
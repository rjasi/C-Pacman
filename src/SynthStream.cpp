#include "SynthStream.h"

#include <iostream>

namespace Pacman
{
    // stream
    SynthStream::SynthStream(unsigned sampleRate)
    : sampleRate_(sampleRate)
    {
        // SFML 3: initialize(channelCount, sampleRate, channelMapVector)
        initialize(1, sampleRate_, { sf::SoundChannel::Mono });
        samples_.resize(chunkFrames_);
    }

    float SynthStream::lerp(float a, float b, float t) 
    { 
        return a + (b - a) * t; 
    }

    void SynthStream::start() 
    { 
        play(); // smfl api function
    }

    void SynthStream::playSfx(const SfxSpec& s) 
    {
        std::lock_guard<std::mutex> lock(mtx_);
        sfx_.push_back(Voice::makeSfx(s, sampleRate_));
    }

    // float SynthStream::oscWsgApprox(double phase01) 
    // {
    //     constexpr double twoPi = 6.283185307179586;
    //     double a = std::sin(twoPi * phase01);           // 1st
    //     double b = 0.18 * std::sin(twoPi * 3.0 * phase01); // 3rd
    //     double c = 0.06 * std::sin(twoPi * 5.0 * phase01); // 5th
    //     double d = 0.02 * std::sin(twoPi * 7.0 * phase01); // 7th
    //     double y = a + b + c + d;

    //     // gentle soft clip similar to analog “rounding”
    //     y = std::tanh(y * 1.2);
    //     return (float)y;
    // }

    float SynthStream::nextSample(Voice& v) 
    {
        float hz = v.startHz;

        // sweep for SFX
        if (!v.infinite && v.durFrames > 1) 
        {
            float t = (float)v.ageFrames / (float)(v.durFrames - 1);
            hz = lerp(v.startHz, v.endHz, t);
        }

        // // LFO FM for ambient
        // if (v.infinite && v.lfoHz > 0.f && v.lfoDepthHz != 0.f) {
        //     float l = oscBasic(v.lfoWave, v.lfoPhase);
        //     hz += l * v.lfoDepthHz;

        //     v.lfoPhase += (double)v.lfoHz / (double)sampleRate_;
        //     v.lfoPhase -= std::floor(v.lfoPhase);
        // }

        // advance carrier phase
        v.phase += (double)hz / (double)sampleRate_;
        v.phase -= std::floor(v.phase); // phase needs to be between [0,1]

        float raw = osc(v.wave, v.phase);
        float out = raw * v.gain * v.envelope();

        v.ageFrames++;
        return out;
    }


    float SynthStream::osc(Wave w, double phase01) 
    {
        constexpr double twoPi = 6.283185307179586; // A sine wave completes one full cycle over 2π radians.
        switch (w) 
        {
            case Wave::Sine:
                return (float)std::sin(twoPi * phase01);
            case Wave::Square:
                return (phase01 < 0.5) ? 1.f : -1.f;
            case Wave::Triangle: 
            {
                double x = phase01;
                double tri = (x < 0.5) ? (4.0 * x - 1.0) : (-4.0 * x + 3.0);
                return (float)tri;
            }
                
            case Wave::Saw:
                return (float)(2.0 * phase01 - 1.0);
            case Wave::WsgApprox: // adapted from https://github.com/livingston/google-pacman/blob/main/pacman-audio.js
            {
                double a = std::sin(twoPi * phase01);           // 1st
                double b = 0.18 * std::sin(twoPi * 3.0 * phase01); // 3rd
                double c = 0.06 * std::sin(twoPi * 5.0 * phase01); // 5th
                double d = 0.02 * std::sin(twoPi * 7.0 * phase01); // 7th
                double y = a + b + c + d;

                // gentle soft clip similar to analog “rounding”
                y = std::tanh(y * 1.2);
                return (float)y;
            }   
                
            default:
                return 0.f;
        }
    }

    bool SynthStream::onGetData(Chunk& data) 
    {
        // Copy voice state out under lock (keep audio thread lock short)
        std::vector<Voice> sfxCopy;
        std::optional<Voice> ambientCopy;
        {
            std::lock_guard<std::mutex> lock(mtx_);
            sfxCopy = sfx_;
            ambientCopy = ambient_;
        }

        for (std::size_t i = 0; i < chunkFrames_; i++) 
        {
            float mix = 0.f;

            for (auto& v : sfxCopy) mix += nextSample(v);
            if (ambientCopy) mix += nextSample(*ambientCopy);

            mix = std::clamp(mix, -1.f, 1.f);
            samples_[i] = (std::int16_t)std::lround(mix * 32767.f);
        }

        // Write back updated phases/ages, remove finished
        {
            std::lock_guard<std::mutex> lock(mtx_);

            // update sfx states (same order)
            for (std::size_t i = 0; i < sfxCopy.size() && i < sfx_.size(); i++)
            {
                sfx_[i] = sfxCopy[i];
            }

            // remove completed voices
            sfx_.erase(
                std::remove_if(sfx_.begin(), sfx_.end(),
                               [](const Voice& v)
                               { 
                                    return v.finished(); 
                                }),
                sfx_.end()
            );

            if (ambientCopy) 
            {
                ambient_ = *ambientCopy;
            }
        }

        data.samples = samples_.data();
        data.sampleCount = samples_.size();
        return true;
    }



    // voice

    float Voice::envelope() const
    {
        if (infinite) return 1.f;
        if (ageFrames < attackFrames)
            return (float)ageFrames / (float)attackFrames;

        std::uint64_t left = (durFrames > ageFrames) ? (durFrames - ageFrames) : 0;
        if (left < releaseFrames)
            return (float)left / (float)releaseFrames;

        return 1.f;
    }

    bool Voice::finished() const 
    { 
        return !infinite && ageFrames >= durFrames; 
    }



}
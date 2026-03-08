#pragma once

#include "Dir.h"
#include "Animation.h"
#include "GhostAnimationPack.h"
#include "PacmanAnimationPack.h"

namespace Pacman
{
    // dumb objects that store position data
    // and animation clipp
    class CutsceneActor
    {
        public:
            virtual ~CutsceneActor() = default;
            CutsceneActor()
            {
                
            }
            // virtual void update(sf::Time dt) = 0;
            // virtual void draw(sf::RenderTarget& rt) = 0;

            virtual void setPosition(sf::Vector2f pos)
            {
                pos_ = pos;
            }

            virtual sf::Vector2f position()
            {
                return pos_;
            }

            virtual void setSpeed(float speed)
            {
                speed_ = speed;
            }

            virtual float speed()
            {
                return speed_;
            }

            virtual void setDirection(Dir dir)
            {
                currentDir_ = dir;
            }

            virtual Dir direction() const
            {
                return currentDir_;
            }


            virtual void render(sf::RenderTarget& window) = 0;
            virtual void update(sf::Time dt) = 0;

            // virtual void setVisible(bool visible) = 0;
            // virtual bool visible() const = 0;

        protected:
            float speed_ = 60.f;
            Dir currentDir_;
            sf::Vector2f pos_;

            void move(sf::Time dt, Dir d)
            {
                sf::Vector2f step = DirUtils::dirVecWorld(d) * (speed_ * dt.asSeconds());
                pos_ += step;
            }
    };

    class GhostActor : public CutsceneActor
    {
        public:
            GhostActor(GhostAnimationPack&& animPack)
            : animPack_(std::move(animPack)) 
            {

            }

            void render(sf::RenderTarget& window) override
            {
                Animation& clip = animPack_.animationFor(state_).clipFor(currentDir_);
                clip.sprite().setPosition(pos_);
                window.draw(clip.sprite());
            }

            void update(sf::Time dt) override
            {
                move(dt, currentDir_);
            }

        private:
            GhostAnimationPack animPack_;
            GhostState state_ = GhostState::Chase;
    };

    // class PacmanActor : public ICutsceneActor
    // {
    //     private:
    //         PacmanAnimationPack& animPack_;
    // };
}
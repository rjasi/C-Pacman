#pragma once

#include "Dir.h"
#include "Animation.h"
#include "GhostAnimationPack.h"
#include "PacmanAnimationPack.h"
#include "PacmanState.h"
#include "MoveableEntity.h"
#include "AtlasRegion.h"

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

            virtual void freeze(bool freeze)
            {
                freeze_ = freeze;
            }

            virtual void setVisible(bool visible)
            {
                visible_ = visible;
            }

            virtual bool visible() const
            {
                return visible_;
            }

            virtual void render(sf::RenderTarget& window) = 0;
            virtual void update(sf::Time dt) = 0;

            // virtual void setVisible(bool visible) = 0;
            // virtual bool visible() const = 0;

        protected:
            float speed_ = 60.f;
            Dir currentDir_ = Dir::None;
            sf::Vector2f pos_;
            bool freeze_ = false;
            bool visible_ = false;

            void move(sf::Time dt, Dir d)
            {
                sf::Vector2f step = DirUtils::dirVecWorld(d) * (speed_ * MoveableEntity::BASE_SPEED * dt.asSeconds());
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
                if (!visible_)
                {
                    return;
                }
                Animation& clip = animPack_.animationFor(state_).clipFor(currentDir_);
                clip.sprite().setPosition(pos_);
                window.draw(clip.sprite());
            }

            void update(sf::Time dt) override
            {

                if (freeze_)
                {
                    return;
                }
                move(dt, currentDir_);

                animPack_.update(dt);
            }

            void setState(GhostState state)
            {
                state_ = state;
            }

        private:
            GhostAnimationPack animPack_;
            GhostState state_ = GhostState::Chase;
    };

    class PacmanActor : public CutsceneActor
    {
        public:
            PacmanActor(PacmanAnimationPack animPack)
            : animPack_(std::move(animPack))
            {

            }

            void render(sf::RenderTarget& window) override
            {
                if (!visible_)
                {
                    return;
                }
                Animation& clip = animPack_.animationFor(state_).clipFor(currentDir_);
                clip.sprite().setPosition(pos_);
                window.draw(clip.sprite());
            }

            void update(sf::Time dt) override
            {

                if (freeze_)
                {
                    return;
                }
                move(dt, currentDir_);

                animPack_.update(dt);
            }

            void setState(PacmanState state)
            {
                state_ = state;
            }
            
        private:
            PacmanState state_ = PacmanState::Normal;
            PacmanAnimationPack animPack_;
    };

    class Prop : public sf::Sprite
    {
        public: 
            Prop(sf::Texture& texture, const Atlas::AtlasRegion& region, const sf::Vector2f& origin = {8.f, 8.f}, bool visible = false)
            : sf::Sprite(texture),
            visible_(visible)
            {
                setTextureRect(region.IntRect());
                setOrigin(origin);
            }

            Prop() = delete;
     
            void setVisible(bool visible)
            {
                visible_ = visible;
            }
            
            bool visible() const
            {
                return visible_;
            }

        private:
            bool visible_ = false;
    };
}
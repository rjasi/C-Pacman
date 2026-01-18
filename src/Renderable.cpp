#include "Renderable.h"

namespace Pacman
{
    Renderable::Renderable(DirectionalAnimation* animationClips,
                        const MoveableEntity* entity)
    : animationClips_(animationClips), 
    entity_(entity)
    {
        
    }

    void Renderable::update(sf::Time dt)
    {
        
    }

    void Renderable::draw(sf::RenderTarget& window)
    {
        auto anim = animationClips_->clipFor(entity_->direction());
        anim->sprite().setPosition(entity_->position());
        window.draw(anim->sprite());
    }
}
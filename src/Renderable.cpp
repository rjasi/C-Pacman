#include "Renderable.h"

namespace Pacman
{
    Renderable::Renderable(IAnimationResolver* animationResolver,
                        const MoveableEntity* entity)
    : animationResolver_(animationResolver), 
    entity_(*entity)
    {
        
    }

    void Renderable::update(sf::Time dt)
    {
        
    }

    void Renderable::draw(sf::RenderTarget& window)
    {
        Animation& anim = animationResolver_->resolve(entity_);
        anim.sprite().setPosition(entity_.position());
        window.draw(anim.sprite());
    }
}
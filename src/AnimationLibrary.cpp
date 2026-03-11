#include "AnimationLibrary.h"


namespace Pacman
{
    AnimationLibrary::AnimationLibrary(TextureCache& cache)
    : 
    blinkyRight_(cache.get("atlas"), Atlas::BlinkyRight, 2, ghostFrameTime),
    blinkyLeft_(cache.get("atlas"), Atlas::BlinkyLeft, 2, ghostFrameTime),
    blinkyUp_(cache.get("atlas"), Atlas::BlinkyUp, 2, ghostFrameTime),
    blinkyDown_(cache.get("atlas"), Atlas::BlinkyDown, 2, ghostFrameTime),

    pinkyRight_(cache.get("atlas"), Atlas::PinkyRight, 2, ghostFrameTime),
    pinkyLeft_(cache.get("atlas"), Atlas::PinkyLeft, 2, ghostFrameTime),
    pinkyUp_(cache.get("atlas"), Atlas::PinkyUp, 2, ghostFrameTime),
    pinkyDown_(cache.get("atlas"), Atlas::PinkyDown, 2, ghostFrameTime),

    inkyRight_(cache.get("atlas"), Atlas::InkyRight, 2, ghostFrameTime),
    inkyLeft_(cache.get("atlas"), Atlas::InkyLeft, 2, ghostFrameTime),
    inkyUp_(cache.get("atlas"), Atlas::InkyUp, 2, ghostFrameTime),
    inkyDown_(cache.get("atlas"), Atlas::InkyDown, 2, ghostFrameTime),

    clydeRight_(cache.get("atlas"), Atlas::ClydeRight, 2, ghostFrameTime),
    clydeLeft_(cache.get("atlas"), Atlas::ClydeLeft, 2, ghostFrameTime),
    clydeUp_(cache.get("atlas"), Atlas::ClydeUp, 2, ghostFrameTime),
    clydeDown_(cache.get("atlas"), Atlas::ClydeDown, 2, ghostFrameTime),

    blinky_frightened_ghost_(cache.get("atlas"), Atlas::FrightenedGhost, 2, ghostFrightenedFrameTime),
    blinky_frightened_ghostFlash_(cache.get("atlas"), Atlas::FrightenedGhostFlash, 2, ghostFrightenedFrameTime),
    pinky_frightened_ghost_(cache.get("atlas"), Atlas::FrightenedGhost, 2, ghostFrightenedFrameTime),
    pinky_frightened_ghostFlash_(cache.get("atlas"), Atlas::FrightenedGhostFlash, 2, ghostFrightenedFrameTime),
    inky_frightened_ghost_(cache.get("atlas"), Atlas::FrightenedGhost, 2, ghostFrightenedFrameTime),
    inky_frightened_ghostFlash_(cache.get("atlas"), Atlas::FrightenedGhostFlash, 2, ghostFrightenedFrameTime),
    clyde_frightened_ghost_(cache.get("atlas"), Atlas::FrightenedGhost, 2, ghostFrightenedFrameTime),
    clyde_frightened_ghostFlash_(cache.get("atlas"), Atlas::FrightenedGhostFlash, 2, ghostFrightenedFrameTime),
    blinkyEyes_(MakeEyes(cache.get("atlas"))),
    pinkyEyes_(MakeEyes(cache.get("atlas"))),
    inkyEyes_(MakeEyes(cache.get("atlas"))),
    clydeEyes_(MakeEyes(cache.get("atlas"))),
    
    pacman_normal(MakeNormalCharacter(cache.get("atlas"), GameCharacters::Pacman, 2, pacmanFrameTime)),
    blinky_normal(&blinkyUp_, &blinkyDown_, &blinkyLeft_, &blinkyRight_),
    pinky_normal(&pinkyUp_, &pinkyDown_, &pinkyLeft_, &pinkyRight_),
    inky_normal(&inkyUp_, &inkyDown_, &inkyLeft_, &inkyRight_),
    clyde_normal(&clydeUp_, &clydeDown_, &clydeLeft_, &clydeRight_),

    blinky_fightened_ghost_directional_anim(&blinky_frightened_ghost_),
    blinky_fightened_ghost_flash_directional_anim(&blinky_frightened_ghostFlash_),
    pinky_fightened_ghost_directional_anim(&pinky_frightened_ghost_),
    pinky_fightened_ghost_flash_directional_anim(&pinky_frightened_ghostFlash_),
    inky_fightened_ghost_directional_anim(&inky_frightened_ghost_),
    inky_fightened_ghost_flash_directional_anim(&inky_frightened_ghostFlash_),
    clyde_fightened_ghost_directional_anim(&clyde_frightened_ghost_),
    clyde_fightened_ghost_flash_directional_anim(&clyde_frightened_ghostFlash_),

    blinkyEyesDirectionalAnim_(blinkyEyes_),
    pinkyEyesDirectionalAnim_(pinkyEyes_),
    inkyEyesDirectionalAnim_(inkyEyes_),
    clydeEyesDirectionalAnim_(clydeEyes_),

    pacman(MakeNormalCharacter(cache.get("atlas"), GameCharacters::Pacman, 2, pacmanFrameTime), DirectionalAnimation{Animation{cache.get("atlas"), Atlas::PacmanLastFrame, 1, sf::Time::Zero}}),
    blinky(GameCharacters::Blinky, &blinky_normal, &blinky_fightened_ghost_directional_anim, &blinky_fightened_ghost_flash_directional_anim, &blinkyEyesDirectionalAnim_),
    pinky(GameCharacters::Pinky, &pinky_normal, &pinky_fightened_ghost_directional_anim, &pinky_fightened_ghost_flash_directional_anim, &pinkyEyesDirectionalAnim_),
    inky(GameCharacters::Inky, &inky_normal, &inky_fightened_ghost_directional_anim, &inky_fightened_ghost_flash_directional_anim, &inkyEyesDirectionalAnim_),
    clyde(GameCharacters::Clyde, &clyde_normal, &clyde_fightened_ghost_directional_anim, &clyde_fightened_ghost_flash_directional_anim, &clydeEyesDirectionalAnim_)
    {
        ghostResolvers_[GameCharactersIndex::BLINKY] = std::make_unique<GhostAnimationResolver>(&blinky);
        ghostResolvers_[GameCharactersIndex::PINKY] = std::make_unique<GhostAnimationResolver>(&pinky);
        ghostResolvers_[GameCharactersIndex::INKY] = std::make_unique<GhostAnimationResolver>(&inky);
        ghostResolvers_[GameCharactersIndex::CLYDE] = std::make_unique<GhostAnimationResolver>(&clyde);

        pacmanResolver_ = std::make_unique<PacmanAnimationResolver>(&pacman);
    }


    void AnimationLibrary::update(sf::Time dt)
    {
        pinky.update(dt);
        inky.update(dt);
        blinky.update(dt);
        clyde.update(dt);
        pacman.update(dt);
    }


    DirArray<Animation> AnimationLibrary::MakeEyes(sf::Texture& atlas) 
    {
        return
        {
            Animation(atlas, Atlas::GhostEyesRight, 1, sf::Time::Zero),
            Animation(atlas, Atlas::GhostEyesLeft,  1, sf::Time::Zero),
            Animation(atlas, Atlas::GhostEyesUp,    1, sf::Time::Zero),
            Animation(atlas, Atlas::GhostEyesDown,  1, sf::Time::Zero),
        };
    }

    DirArray<Animation> AnimationLibrary::MakeNormalCharacter(sf::Texture& atlas, GameCharacters id, int frameCountRow, sf::Time frameTime, sf::Vector2f origin)
    {
        Atlas::DirRegions regions = Atlas::NormalRegionsFor(id);
        switch (id)
        {
            case GameCharacters::Pacman:
                return
                {
                    Animation(atlas, regions.right, frameCountRow, frameTime, origin, 0, {Atlas::PacmanLastFrame.IntRect()}),
                    Animation(atlas, regions.left,  frameCountRow, frameTime, origin, 0, {Atlas::PacmanLastFrame.IntRect()}),
                    Animation(atlas, regions.up,    frameCountRow, frameTime, origin, 0, {Atlas::PacmanLastFrame.IntRect()}),
                    Animation(atlas, regions.down,  frameCountRow, frameTime, origin, 0, {Atlas::PacmanLastFrame.IntRect()}),
                };
            default:
                return
                {
                    Animation(atlas, regions.right, frameCountRow, frameTime, origin),
                    Animation(atlas, regions.left,  frameCountRow, frameTime, origin),
                    Animation(atlas, regions.up,    frameCountRow, frameTime, origin),
                    Animation(atlas, regions.down,  frameCountRow, frameTime, origin),
                };

        }
    }

    Animation AnimationLibrary::MakeFrightenedGhost(sf::Texture& atlas, int frameCount, sf::Time frameTime, sf::Vector2f origin)
    {
        return Animation(atlas, Atlas::FrightenedGhost, frameCount, frameTime, origin);
    }

    Animation AnimationLibrary::MakeFrightenedGhostFlash(sf::Texture& atlas, int frameCount, sf::Time frameTime, sf::Vector2f origin)
    {
        return Animation(atlas, Atlas::FrightenedGhostFlash, frameCount, frameTime, origin);
    }

    GhostAnimationPack AnimationLibrary::MakeGhostAnimationPack(sf::Texture& atlas, GameCharacters id)
    {
        auto normalAnim = DirectionalAnimation(MakeNormalCharacter(atlas, id, 2, ghostFrameTime));
        auto frightened = DirectionalAnimation(MakeFrightenedGhost(atlas, 2, ghostFrightenedFrameTime));
        auto frightenedFlash_ = DirectionalAnimation(MakeFrightenedGhostFlash(atlas, 2, ghostFrightenedFrameTime));
        auto eyes = DirectionalAnimation(MakeEyes(atlas));
        return GhostAnimationPack(id, normalAnim, frightened, frightenedFlash_, eyes);
    }

}
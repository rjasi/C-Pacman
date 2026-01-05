#include "TextureCache.h"

#include <iostream>

namespace Pacman
{
    sf::Texture& TextureCache::get(const std::string& key)
    {
        auto it = textures_.find(key);
        if (it == textures_.end())
            throw std::runtime_error("Texture not loaded: " + key);
        return it->second;
    }

    sf::Texture& TextureCache::load(const std::string& key, const std::string& path, bool smooth)
    {
        auto [it, inserted] = textures_.try_emplace(key);
        sf::Texture& tex = it->second;

        if (inserted) {
            if (!tex.loadFromFile(path))
                throw std::runtime_error("Failed to load texture: " + path);
            // for pixel art: set false to avoid blur when scaling
            tex.setSmooth(smooth);
        }
        return tex;
    }

    bool TextureCache::has(const std::string& key) const 
    { 
        return textures_.contains(key); 
    }

}
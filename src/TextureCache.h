#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <stdexcept>

namespace Pacman 
{

    class TextureCache 
    {
        public:
            TextureCache() = default;
            sf::Texture& get(const std::string& key);
            sf::Texture& load(const std::string& key, const std::string& path, bool smooth = false);
            bool has(const std::string& key) const;

            TextureCache(const TextureCache& cache) = delete;
            TextureCache& operator=(const TextureCache& cache) = delete;

        private:
            std::unordered_map<std::string, sf::Texture> textures_;
    };
}
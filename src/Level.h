#include <vector>

namespace Pacman
{
    class Level 
    {
        private: 
            int height;
            int width; 

            std::vector<std::string> tiles;

            static const int TILE_SIZE = 32;

        public:
            bool isTile(int x, int y);

            bool loadFromFile(const std::string& location);

            const std::vector<std::string>& getTiles();

    };
}
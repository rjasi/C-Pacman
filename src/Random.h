

#include <limits>
#include <cmath>
#include <vector>
#include <random>

namespace Pacman
{
    inline int randomInt(int min, int max)
    {
        static std::random_device rd;              // non-deterministic seed
        static std::mt19937 gen(rd());              // Mersenne Twister engine
        std::uniform_int_distribution<int> dist(min, max);

        return dist(gen);
    }
}


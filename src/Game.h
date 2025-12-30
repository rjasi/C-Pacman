#include "Level.h"

namespace Pacman
{
    class Game 
    {
        private: 
            Level level; 
            int score; 
            int lives;

        public: 
            Game();

            void printLevel();

            void foo(int&);
            void foo(const int&);

    };
}
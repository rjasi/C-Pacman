#pragma once

#include <string>
#include <iostream>
#include <fstream>

namespace Pacman
{
    enum class LogLevel
    {
        Info,
        Warn,
        Error
    };

    class Logger 
    {
        public: 
            static Logger& instance();
            
            void info(const std::string& message);
            void warn(const std::string& message);
            void error(const std::string& message);

        private: 
            Logger();
            ~Logger() = default;
            std::ofstream file_;

            Logger(const Logger&) = delete;
            Logger& operator=(const Logger&) = delete;

    };
}
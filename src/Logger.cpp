#include "Logger.h"

#include <filesystem>
#include <cstdlib>

namespace Pacman
{
    Logger& Logger::instance()
    {
        static Logger logger;
        return logger;
    }

    Logger::Logger()
    {
        const char* home = std::getenv("HOME");
        if (!home) 
        {
            std::cerr << "[LOGGER] HOME not set\n";
            return;
        }

        std::filesystem::path logDir = std::filesystem::path(home) /"Library/Application Support/Pacman";

        std::filesystem::create_directories(logDir);

        std::filesystem::path logFile = logDir / "pacman.log";

        file_.open(logFile, std::ios::out | std::ios::trunc);
        if (!file_) 
        {
            std::cerr << "[LOGGER] Failed to open log file: "
                    << logFile << '\n';
        }
    }


    void Logger::info(const std::string& message)
    {
        file_ << "[INFO]: " <<  message;
        std::cerr << "[INFO]: " << message;
    }


}
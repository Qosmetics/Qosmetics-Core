#pragma once
#include "beatsaber-hook/shared/utils/logging.hpp"
#include <string_view>

#include "paper/shared/logger.hpp"

namespace Qosmetics::Core
{
    class Logging
    {
    public:
        static Logger& getLogger();
        static LoggerContextObject& getContextLogger(const char* fun, const char* file, int line);
    };
}

#define INFO(...) Paper::Logger::fmtLog<Paper::LogLevel::INF>(__VA_ARGS__)
#define ERROR(...) Paper::Logger::fmtLog<Paper::LogLevel::ERR>(__VA_ARGS__)
#define CRITICAL(...) Paper::Logger::fmtLog<Paper::LogLevel::ERR>(__VA_ARGS__)
#define DEBUG(...) Paper::Logger::fmtLog<Paper::LogLevel::DBG>(__VA_ARGS__)

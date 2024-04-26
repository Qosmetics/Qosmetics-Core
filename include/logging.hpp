#pragma once
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include <string_view>

#include "paper/shared/logger.hpp"

#define INFO(str, ...) Paper::Logger::fmtLogTag<Paper::LogLevel::INF>(str, "QosmeticsCore" __VA_OPT__(, __VA_ARGS__))
#define ERROR(str, ...) Paper::Logger::fmtLogTag<Paper::LogLevel::ERR>(str, "QosmeticsCore" __VA_OPT__(, __VA_ARGS__))
#define CRITICAL(str, ...) Paper::Logger::fmtLogTag<Paper::LogLevel::ERR>(str, "QosmeticsCore" __VA_OPT__(, __VA_ARGS__))
#define DEBUG(str, ...) Paper::Logger::fmtLogTag<Paper::LogLevel::DBG>(str, "QosmeticsCore" __VA_OPT__(, __VA_ARGS__))

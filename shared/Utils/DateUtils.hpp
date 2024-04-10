#pragma once

#include "../_config.h"
#include <time.h>

namespace Qosmetics::Core::DateUtils
{
    QOSMETICS_CORE_EXPORT struct tm GetTime();
    QOSMETICS_CORE_EXPORT bool isMonth(int month);
    QOSMETICS_CORE_EXPORT bool isDayOfMonth(int day);
    QOSMETICS_CORE_EXPORT bool isDayOfWeek(int day);
    QOSMETICS_CORE_EXPORT bool isDayOfYear(int day);
}

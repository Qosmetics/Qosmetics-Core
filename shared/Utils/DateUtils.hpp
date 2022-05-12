#pragma once
#include <time.h>

namespace Qosmetics::Core::DateUtils
{
    struct tm GetTime();
    bool isMonth(int month);
    bool isDayOfMonth(int day);
    bool isDayOfWeek(int day);
    bool isDayOfYear(int day);
}
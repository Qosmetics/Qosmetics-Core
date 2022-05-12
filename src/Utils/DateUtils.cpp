#include "Utils/DateUtils.hpp"

namespace Qosmetics::Core::DateUtils
{
    struct tm GetTime()
    {
        time_t rawtime = time(nullptr);
        return *localtime(&rawtime);
    }

    bool isMonth(int month)
    {
        return (month - 1) == GetTime().tm_mon;
    }

    bool isDayOfMonth(int day)
    {
        return day == GetTime().tm_mday;
    }

    bool isDayOfWeek(int day)
    {
        return (day - 1) == GetTime().tm_wday;
    }

    bool isDayOfYear(int day)
    {
        return (day - 1) == GetTime().tm_yday;
    }
}
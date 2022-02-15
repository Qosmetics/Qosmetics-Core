#include "Utils/RainbowUtils.hpp"
#define RAINBOW_COLORS 12

namespace Qosmetics::Core::RainbowUtils
{
    static inline int rainbowIndex = rand() % RAINBOW_COLORS;
    static constexpr int colorSegmentSize = 24;
    static const char colorPrefix[RAINBOW_COLORS][16] = {
        "<color=#ff6060>",
        "<color=#ffa060>",
        "<color=#ffff60>",
        "<color=#a0ff60>",
        "<color=#60ff60>",
        "<color=#60ffa0>",
        "<color=#60ffff>",
        "<color=#60a0ff>",
        "<color=#6060ff>",
        "<color=#a060ff>",
        "<color=#ff60ff>",
        "<color=#ff60a0>"};

    bool shouldRainbow(std::string_view name)
    {
        return toLower(std::string(name)).find("rainbow") != std::string::npos;
    }

    bool shouldRainbow(UnityEngine::Color& color)
    {
        return color.r >= 0.99f && color.g >= 0.99f && color.b >= 0.99f;
    }

    std::string rainbowify(std::string_view in)
    {
        std::string result;
        int size = in.size();
        int finalSize = size * sizeof(char) * colorSegmentSize;
        result.resize(finalSize);
        for (int i = 0; i < size; i++)
        {
            auto currentStart = &result[i * colorSegmentSize];
            memcpy(currentStart, colorPrefix[rainbowIndex], 15);
            currentStart[15] = in[i];
            memcpy(&currentStart[16], "</color>", 8);
            rainbowIndex++;
            rainbowIndex %= RAINBOW_COLORS;
        }
        return result;
    }

    std::string toLower(std::string in)
    {
        for (auto& c : in)
            c = tolower(c);
        return in;
    }
}
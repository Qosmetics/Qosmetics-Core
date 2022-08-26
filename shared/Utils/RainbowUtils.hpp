#pragma once
#include "UnityEngine/Color.hpp"

#include <string>
namespace Qosmetics::Core::RainbowUtils
{
    bool shouldRainbow(std::string_view name);
    bool shouldRainbow(UnityEngine::Color& color);
    std::string rainbowify(std::string_view in);
    std::string gayify(std::string_view in);
    std::string toLower(std::string in);
}
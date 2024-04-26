#pragma once

#include "../_config.h"
#include "UnityEngine/Color.hpp"
#include <string>
namespace Qosmetics::Core::RainbowUtils
{
    QOSMETICS_CORE_EXPORT bool shouldRainbow(std::string_view name);
    QOSMETICS_CORE_EXPORT bool shouldRainbow(UnityEngine::Color& color);
    QOSMETICS_CORE_EXPORT std::string rainbowify(std::string_view in);
    QOSMETICS_CORE_EXPORT std::string gayify(std::string_view in);
    QOSMETICS_CORE_EXPORT std::string toLower(std::string in);

    QOSMETICS_CORE_EXPORT const std::string_view rainbowGradient();
    QOSMETICS_CORE_EXPORT const std::string_view randomGradient();
}

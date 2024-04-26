#pragma once

#include "../_config.h"
#include "HMUI/TitleViewController.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/Color.hpp"
#include <string>

namespace Qosmetics::Core::UIUtils
{

    /// @brief sets the color for a given title view, can turn off the button animation if needed
    /// @param titleView the titleview to set the color for
    /// @param color the color to set
    /// @param buttonanim whether the button animation should work (this prevents colors from being weird)
    QOSMETICS_CORE_EXPORT void SetTitleColor(HMUI::TitleViewController* titleView, const UnityEngine::Color& color, bool buttonanim = false);

}

#pragma once

#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Color.hpp"
#include <string>

class UIUtils
{
    public:
        static TMPro::TextMeshProUGUI* AddHeader(UnityEngine::Transform* parent, std::string title);
        static TMPro::TextMeshProUGUI* AddHeader(UnityEngine::Transform* parent, std::string title, UnityEngine::Color color);
        static TMPro::TextMeshProUGUI* AddHeader(UnityEngine::Transform* parent, std::string title, UnityEngine::Color leftColor, UnityEngine::Color rightColor);
};
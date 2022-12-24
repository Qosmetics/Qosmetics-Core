#pragma once

#include "UnityEngine/UI/Button.hpp"
#include "bsml/shared/BSML/Tags/ButtonTag.hpp"

namespace Qosmetics::Core
{
    class ImageButtonTag : public BSML::BSMLTag
    {
    public:
        ImageButtonTag() : BSMLTag() {}

    protected:
        virtual UnityEngine::GameObject* CreateObject(UnityEngine::Transform* parent) const override;
        virtual UnityEngine::UI::Button* get_buttonPrefab() const;
    };
}
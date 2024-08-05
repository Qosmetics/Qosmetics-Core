#include "Utils/UIUtils.hpp"
#include "logging.hpp"

#include "HMUI/ButtonStaticAnimations.hpp"
#include "HMUI/CurvedCanvasSettingsHelper.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSML/Components/Backgroundable.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

Color operator*(const Color& col, float v) {
    return {
        col.r * v,
        col.g * v,
        col.b * v,
        col.a * v
    };
}

namespace Qosmetics::Core::UIUtils {
    void SetTitleColor(HMUI::TitleViewController* titleView, const UnityEngine::Color& color, bool buttonanim) {
        Transform* title_T = titleView->get_transform();
        Transform* BG_T = title_T->Find("BG");
        Transform* BackButtonBG_T = title_T->Find("BackButton/BG");

        HMUI::ImageView* imageView = BG_T->get_gameObject()->GetComponent<HMUI::ImageView*>();
        Color oldColor = imageView->get_color();

        imageView->set_color(color);

        HMUI::ImageView* buttonImageView = BackButtonBG_T->get_gameObject()->GetComponent<HMUI::ImageView*>();
        buttonImageView->set_color(color);
        buttonImageView->set_color0(color);
        buttonImageView->set_color1(color * 0.9f);

        HMUI::ButtonStaticAnimations* anim = BackButtonBG_T->get_parent()->get_gameObject()->GetComponent<HMUI::ButtonStaticAnimations*>();
        anim->set_enabled(buttonanim);
    }
}

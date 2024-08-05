#include "UI/QosmeticsBaseFlowCoordinator.hpp"
#include "logging.hpp"

#include "HMUI/ButtonSpriteSwap.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/TextureWrapMode.hpp"

#include "bsml/shared/Helpers/delegates.hpp"
#include "bsml/shared/Helpers/getters.hpp"

DEFINE_TYPE(Qosmetics::Core, QosmeticsBaseFlowCoordinator);

namespace Qosmetics::Core {
    void QosmeticsBaseFlowCoordinator::ctor() {
        HMUI::FlowCoordinator::_ctor();
    }

    void QosmeticsBaseFlowCoordinator::Present() {
        if (!qosmeticsFlowCoordinator || !qosmeticsFlowCoordinator->m_CachedPtr.m_value) return;

        auto currentFlowCoordinator = BSML::Helpers::GetMainFlowCoordinator()->YoungestChildFlowCoordinatorOrSelf();
        // if we are already in the qos FC then just start presenting ourselves
        if (currentFlowCoordinator.unsafePtr() == qosmeticsFlowCoordinator) {
            DEBUG("Presenting {} on parent {}", fmt::ptr(this), fmt::ptr(qosmeticsFlowCoordinator));
            qosmeticsFlowCoordinator->PresentFlowCoordinator(this, nullptr, HMUI::ViewController::AnimationDirection::Horizontal, false, false);
            return;
        }

        DEBUG("We were not on the qosmetics flow coordinator, presenting a new flow coordinator after the qosmetics one!");
        auto onFinished = BSML::MakeSystemAction(
            [this]() {
                DEBUG("Post present presenting specific flow coordinator {}::{}", klass->namespaze, klass->name);
                qosmeticsFlowCoordinator->PresentFlowCoordinator(this, nullptr, HMUI::ViewController::AnimationDirection::Horizontal, false, false);
            }
        );
        currentFlowCoordinator->PresentFlowCoordinator(qosmeticsFlowCoordinator, onFinished, HMUI::ViewController::AnimationDirection::Horizontal, true, false);
    }

    StringW QosmeticsBaseFlowCoordinator::get_menuName() { return name ? name : "Unknown"; }

    void QosmeticsBaseFlowCoordinator::PostParse() {
        activeSprite->texture->wrapMode = UnityEngine::TextureWrapMode::Clamp;
        inActiveSprite->texture->wrapMode = UnityEngine::TextureWrapMode::Clamp;

        auto spriteSwap = button->GetComponent<HMUI::ButtonSpriteSwap*>();

        // setting the sprites
        spriteSwap->_highlightStateSprite = activeSprite;
        spriteSwap->_pressedStateSprite = activeSprite;

        spriteSwap->_disabledStateSprite = inActiveSprite;
        spriteSwap->_normalStateSprite = inActiveSprite;
    }

    void QosmeticsBaseFlowCoordinator::DidActivate_Base(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        auto didactivate = il2cpp_utils::FindMethodUnsafe(this, "DidActivate", 3);
        if (didactivate)
            il2cpp_utils::RunMethod(this, didactivate, firstActivation, addedToHierarchy, screenSystemEnabling);
    }
}

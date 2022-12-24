#include "UI/QosmeticsBaseFlowCoordinator.hpp"
#include "logging.hpp"

#include "HMUI/ButtonSpriteSwap.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/TextureWrapMode.hpp"

#include "HMUI/ViewController_AnimationDirection.hpp"
#include "bsml/shared/Helpers/delegates.hpp"
#include "bsml/shared/Helpers/getters.hpp"

DEFINE_TYPE(Qosmetics::Core, QosmeticsBaseFlowCoordinator);

namespace Qosmetics::Core
{
    void QosmeticsBaseFlowCoordinator::ctor()
    {
        static auto baseKlass = classof(HMUI::FlowCoordinator*);
        custom_types::InvokeBaseCtor(baseKlass, this);
    }

    void QosmeticsBaseFlowCoordinator::Present()
    {
        if (qosmeticsFlowCoordinator && qosmeticsFlowCoordinator->m_CachedPtr.m_value)
        {
            auto currentFlowCoordinator = BSML::Helpers::GetMainFlowCoordinator()->YoungestChildFlowCoordinatorOrSelf();
            // if we aren't in the qos FC rn, present it and then present the proper one
            if (currentFlowCoordinator != qosmeticsFlowCoordinator)
            {
                DEBUG("We were not on the qosmetics flow coordinator, presenting a new flow coordinator after the qosmetics one!");
                auto onFinished = BSML::MakeSystemAction(
                    [this]()
                    {
                        DEBUG("Post present presenting specific flow coordinator {}::{}", klass->namespaze, klass->name);
                        qosmeticsFlowCoordinator->PresentFlowCoordinator(this, nullptr, HMUI::ViewController::AnimationDirection::Horizontal, false, false);
                    });
                currentFlowCoordinator->PresentFlowCoordinator(qosmeticsFlowCoordinator, onFinished, HMUI::ViewController::AnimationDirection::Horizontal, true, false);
            }
            else
            {
                // if we are already in the qos FC then just present this one
                DEBUG("Presenting {} on parent {}", fmt::ptr(this), fmt::ptr(qosmeticsFlowCoordinator));
                qosmeticsFlowCoordinator->PresentFlowCoordinator(this, nullptr, HMUI::ViewController::AnimationDirection::Horizontal, false, false);
            }
        }
    }

    StringW QosmeticsBaseFlowCoordinator::get_menuName()
    {
        return name ? name : "Unknown";
    }

    void QosmeticsBaseFlowCoordinator::PostParse()
    {
        activeSprite->get_texture()->set_wrapMode(UnityEngine::TextureWrapMode::Clamp);
        inActiveSprite->get_texture()->set_wrapMode(UnityEngine::TextureWrapMode::Clamp);

        auto spriteSwap = button->GetComponent<HMUI::ButtonSpriteSwap*>();

        // setting the sprites
        spriteSwap->highlightStateSprite = activeSprite;
        spriteSwap->pressedStateSprite = activeSprite;

        spriteSwap->disabledStateSprite = inActiveSprite;
        spriteSwap->normalStateSprite = inActiveSprite;
    }

    void QosmeticsBaseFlowCoordinator::DidActivate_Base(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        auto didactivate = il2cpp_utils::FindMethodUnsafe(this, "DidActivate", 3);
        if (didactivate)
            il2cpp_utils::RunMethod(this, didactivate, firstActivation, addedToHierarchy, screenSystemEnabling);
    }
}

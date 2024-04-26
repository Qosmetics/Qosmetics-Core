#pragma once

#include "custom-types/shared/macros.hpp"

#include "HMUI/FlowCoordinator.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/UI/Button.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Core, QosmeticsBaseFlowCoordinator, HMUI::FlowCoordinator,
                      DECLARE_CTOR(ctor);
                      DECLARE_INSTANCE_FIELD(HMUI::FlowCoordinator*, qosmeticsFlowCoordinator);
                      DECLARE_INSTANCE_FIELD(StringW, name);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, activeSprite);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, inActiveSprite);
                      DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, button);
                      DECLARE_INSTANCE_METHOD(void, PostParse);
                      DECLARE_INSTANCE_METHOD(void, Present);
                      DECLARE_INSTANCE_METHOD(StringW, get_menuName);

                      DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate_Base, &::HMUI::FlowCoordinator::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

)

#pragma once

#include "custom-types/shared/macros.hpp"

#include "HMUI/FlowCoordinator.hpp"
#include "UnityEngine/Sprite.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Core, QosmeticsBaseFlowCoordinator, HMUI::FlowCoordinator,
                      DECLARE_CTOR(ctor);
                      DECLARE_INSTANCE_FIELD(StringW, name);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, activeSprite);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, inActiveSprite);
                      DECLARE_OVERRIDE_METHOD(void, DidActivate_Base, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::HMUI::FlowCoordinator::DidActivate>::get(), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

)
#pragma once

#include "HMUI/ViewController.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"

#include "bsml/shared/BSML/Components/Backgroundable.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "custom-types/shared/macros.hpp"

#define DECLARE_OVERRIDE_METHOD_MATCH(retval, name, mptr, ...) \
    DECLARE_OVERRIDE_METHOD(retval, name, il2cpp_utils::il2cpp_type_check::MetadataGetter<mptr>::get(), __VA_ARGS__)

DECLARE_CLASS_CODEGEN(Qosmetics::Core, CreditViewController, HMUI::ViewController,
                      DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, patronTexts);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, container);
                      DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, placeholderText);

                      DECLARE_INSTANCE_METHOD(StringW, get_thankyou);
                      DECLARE_INSTANCE_METHOD(bool, get_gay);
                      DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::ViewController::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

                      custom_types::Helpers::Coroutine GetPatreonSupporters();

)

DECLARE_CLASS_CODEGEN(Qosmetics::Core, Patron, Il2CppObject,
                      DECLARE_INSTANCE_FIELD(StringW, patronName);
                      DECLARE_CTOR(ctor, StringW patronName);

)

DECLARE_CLASS_CODEGEN(Qosmetics::Core, Tier, Il2CppObject,
                      DECLARE_INSTANCE_FIELD(StringW, tierName);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Color, bannerColor);
                      DECLARE_INSTANCE_FIELD(List<Patron*>*, patrons);
                      DECLARE_INSTANCE_FIELD(BSML::Backgroundable*, banner);

                      DECLARE_INSTANCE_METHOD(void, PostParse);
                      DECLARE_CTOR(ctor, StringW tierName, UnityEngine::Color bannerColor);

)
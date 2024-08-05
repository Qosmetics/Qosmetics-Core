#pragma once

#include "custom-types/shared/coroutine.hpp"
#include "custom-types/shared/macros.hpp"

#include "HMUI/ViewController.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"

#include "Data/Patrons.hpp"
#include "bsml/shared/BSML/Components/Backgroundable.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Core, CreditViewController, HMUI::ViewController,
                      DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, patronTexts);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, container);
                      DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, placeholderText);

                      DECLARE_INSTANCE_METHOD(StringW, get_gaydient);
                      DECLARE_INSTANCE_METHOD(StringW, get_thankyou);
                      DECLARE_INSTANCE_METHOD(bool, get_gay);
                      DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::ViewController::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

                      private :

                      void HandlePatronResponse(PatronResponse response);
                      void UsePatrons(Patrons const& patrons);

)

DECLARE_CLASS_CODEGEN(Qosmetics::Core, Patron, System::Object,
                      DECLARE_INSTANCE_FIELD(StringW, patronName);
                      DECLARE_CTOR(ctor, StringW patronName);

)

DECLARE_CLASS_CODEGEN(Qosmetics::Core, Tier, System::Object,
                      DECLARE_INSTANCE_FIELD(StringW, tierName);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Color, bannerColor);
                      DECLARE_INSTANCE_FIELD(ListW<Patron*>, patrons);
                      DECLARE_INSTANCE_FIELD(BSML::Backgroundable*, banner);

                      DECLARE_INSTANCE_METHOD(void, PostParse);
                      DECLARE_CTOR(ctor, StringW tierName, UnityEngine::Color bannerColor);

)

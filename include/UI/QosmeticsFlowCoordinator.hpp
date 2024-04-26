#pragma once

#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/ViewController.hpp"

#include "beatsaber-hook/shared/utils/typedefs.h"
#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

#include "Zenject/IInitializable.hpp"

#include "CreditViewController.hpp"
#include "ProfileSwitcherViewController.hpp"
#include "QosmeticsViewController.hpp"

#include "bsml/shared/BSML/Components/TextGradientUpdater.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(Qosmetics::Core, QosmeticsFlowCoordinator, HMUI::FlowCoordinator, classof(::Zenject::IInitializable*),

                                 DECLARE_INSTANCE_FIELD(HMUI::ViewController*, profileSwitcherViewController);
                                 DECLARE_INSTANCE_FIELD(HMUI::ViewController*, qosmeticsViewController);
                                 DECLARE_INSTANCE_FIELD(HMUI::ViewController*, creditViewController);
                                 DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, activeSprite);
                                 DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, inactiveSprite);
                                 DECLARE_INSTANCE_FIELD(GlobalNamespace::MainFlowCoordinator*, mainFlowCoordinator);
                                 DECLARE_INSTANCE_FIELD(UnityEngine::UI::Button*, settingsButton);
                                 DECLARE_INSTANCE_FIELD(ListW<UnityEngine::Transform*>, vanillaMenus);
                                 DECLARE_INSTANCE_FIELD(BSML::TextGradientUpdater*, titleGradientUpdater);

                                 DECLARE_INJECT_METHOD(void, Inject, Qosmetics::Core::CreditViewController* creditViewController, Qosmetics::Core::ProfileSwitcherViewController* profileSwitcherViewController, Qosmetics::Core::QosmeticsViewController* qosmeticsViewController, GlobalNamespace::MainFlowCoordinator* mainFlowCoordinator);
                                 DECLARE_INSTANCE_METHOD(void, PostParse);
                                 DECLARE_INSTANCE_METHOD(void, PresentSelf);
                                 DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize, &::Zenject::IInitializable::Initialize);
                                 DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::FlowCoordinator::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
                                 DECLARE_OVERRIDE_METHOD_MATCH(void, DidDeactivate, &HMUI::FlowCoordinator::DidDeactivate, bool removedFromHierarchy, bool screenSystemDisabling);
                                 DECLARE_OVERRIDE_METHOD_MATCH(void, BackButtonWasPressed, &HMUI::FlowCoordinator::BackButtonWasPressed, HMUI::ViewController* topViewController);
                                 DECLARE_CTOR(ctor);

)

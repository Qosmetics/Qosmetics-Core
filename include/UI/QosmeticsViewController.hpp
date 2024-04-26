#pragma once

#include "UI/QosmeticsBaseFlowCoordinator.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

#include "HMUI/ViewController.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Core, QosmeticsViewController, HMUI::ViewController,
                      DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::ViewController::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

                      DECLARE_INJECT_METHOD(void, Inject, ListW<Qosmetics::Core::QosmeticsBaseFlowCoordinator*> baseFlowCoordinators);
                      DECLARE_INSTANCE_FIELD(HMUI::FlowCoordinator*, qosmeticsFlowCoordinator);
                      DECLARE_INSTANCE_METHOD(bool, get_anyCoordinators);
                      DECLARE_INSTANCE_METHOD(void, set_qosmeticsFlowCoordinator, HMUI::FlowCoordinator* qosmeticsFlowCoordinator);

                      DECLARE_INSTANCE_FIELD_DEFAULT(ListW<Qosmetics::Core::QosmeticsBaseFlowCoordinator*>, flowCoordinators, nullptr);
                      DECLARE_DEFAULT_CTOR();

)

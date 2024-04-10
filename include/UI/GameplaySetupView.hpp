#pragma once

#include "System/IDisposable.hpp"
#include "UI/QosmeticsFlowCoordinator.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "Zenject/IInitializable.hpp"
#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(Qosmetics::Core, GameplaySetupView, System::Object, std::vector<Il2CppClass*>({classof(::Zenject::IInitializable*), classof(::System::IDisposable*)}),
                                 DECLARE_INSTANCE_FIELD(Qosmetics::Core::QosmeticsFlowCoordinator*, qosmeticsFlowCoordinator);
                                 DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, grid);

                                 DECLARE_INSTANCE_FIELD_DEFAULT(ListW<Qosmetics::Core::QosmeticsBaseFlowCoordinator*>, flowCoordinators, nullptr);

                                 DECLARE_INJECT_METHOD(void, Inject, Qosmetics::Core::QosmeticsFlowCoordinator* qosmeticsFlowCoordinator, ListW<Qosmetics::Core::QosmeticsBaseFlowCoordinator*> baseFlowCoordinators);
                                 DECLARE_INSTANCE_METHOD(bool, get_anyCoordinators);
                                 DECLARE_INSTANCE_METHOD(void, PostParse);
                                 DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize, &::Zenject::IInitializable::Initialize);
                                 DECLARE_OVERRIDE_METHOD_MATCH(void, Dispose, &::System::IDisposable::Dispose);
                                 DECLARE_DEFAULT_CTOR();

)

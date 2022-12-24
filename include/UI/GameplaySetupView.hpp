#pragma once

#include "UI/QosmeticsFlowCoordinator.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

#define INTERFACES                                                           \
    {                                                                        \
        classof(::Zenject::IInitializable*), classof(::System::IDisposable*) \
    }

___DECLARE_TYPE_WRAPPER_INHERITANCE(Qosmetics::Core, GameplaySetupView, Il2CppTypeEnum::IL2CPP_TYPE_CLASS, Il2CppObject, "Qosmetics::Core", INTERFACES, 0, nullptr,
                                    DECLARE_INSTANCE_FIELD(Qosmetics::Core::QosmeticsFlowCoordinator*, qosmeticsFlowCoordinator);
                                    DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, grid);

                                    DECLARE_INSTANCE_FIELD_DEFAULT(ListWrapper<Qosmetics::Core::QosmeticsBaseFlowCoordinator*>, flowCoordinators, nullptr);

                                    DECLARE_INJECT_METHOD(void, Inject, Qosmetics::Core::QosmeticsFlowCoordinator* qosmeticsFlowCoordinator, ListWrapper<Qosmetics::Core::QosmeticsBaseFlowCoordinator*> baseFlowCoordinators);
                                    DECLARE_INSTANCE_METHOD(bool, get_anyCoordinators);
                                    DECLARE_INSTANCE_METHOD(void, PostParse);
                                    DECLARE_OVERRIDE_METHOD(void, Initialize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::IInitializable::Initialize>::get());
                                    DECLARE_OVERRIDE_METHOD(void, Dispose, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::System::IDisposable::Dispose>::get());
                                    DECLARE_DEFAULT_CTOR();

)
#pragma once
#include "SaberModelController.hpp"

#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/SaberType.hpp"
#include "UnityEngine/Transform.hpp"

#include <type_traits>

namespace Qosmetics::Core::SaberModelFactoryRegister
{
    template <typename T>
    concept ModelController = std::is_convertible_v<T, Qosmetics::Core::SaberModelController*> && requires(T a, GlobalNamespace::Saber* saber)
    {
        a->Init(saber);
    };

    class SaberModelFactory
    {
    public:
        std::string identifier;
        int priority;
        virtual Il2CppReflectionType* get_saberModelControllertype() const = 0;

        SaberModelFactory(std::string_view identifier, int priority) : identifier(identifier), priority(priority){};

        bool operator<(const SaberModelFactory& rhs) const;
    };

    /// @brief register a registration to redecorate something
    /// @param registration the registration to use
    void Register(const SaberModelFactory* registration);
}

#ifndef SABERMODELFACTORY_REGISTRATION
/*
macro to be used in a similiar way to a hook, this makes creating registrations far easier than having to manually manage everythinbg, and ensures registrations are used as intended

example usage:
SABERMODELFACTORY_REGISTRATION(QosmeticsSabers, 10)
{
    // This would be an empty saber object that just got the default Qosmetics::Core::SaberModelController script added to it, it's your job to properly implement a class that inherits that sabermodelcontroller and defines the commented out methods from that header.
    UnityEngine::GameObject* go = UnityEngine::GameObject::New_ctor("LeftSaber")
    return go->AddComponent<Qosmetics::Core::SaberModelController*>();
}
*/
#define SABERMODELFACTORY_REGISTRATION(identifier, priority, modelControllerType)                                                                         \
    template <Qosmetics::Core::SaberModelFactoryRegister::ModelController T>                                                                              \
    struct sabermodelfactory_registration_##identifier##_##priority : Qosmetics::Core::SaberModelFactoryRegister::SaberModelFactory                       \
    {                                                                                                                                                     \
        sabermodelfactory_registration_##identifier##_##priority() : Qosmetics::Core::SaberModelFactoryRegister::SaberModelFactory(#identifier, priority) \
        {                                                                                                                                                 \
            Qosmetics::Core::SaberModelFactoryRegister::Register(this);                                                                                   \
        }                                                                                                                                                 \
        Il2CppReflectionType* get_saberModelControllertype() const override { return csTypeOf(T); };                                                      \
    };                                                                                                                                                    \
    static sabermodelfactory_registration_##identifier##_##priority<modelControllerType> sabermodelfactory_registration_##identifier##_##priorityInstance = sabermodelfactory_registration_##identifier##_##priority<modelControllerType>()
#endif

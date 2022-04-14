#pragma once
#include "SaberModelController.hpp"

#include "GlobalNamespace/SaberType.hpp"
#include "UnityEngine/Transform.hpp"

namespace Qosmetics::Core::SaberModelFactoryRegister
{
    class SaberModelFactory
    {
    public:
        std::string identifier;
        int priority;
        SaberModelFactory(std::string_view identifier, int priority) : identifier(identifier), priority(priority){};

        bool operator<(const SaberModelFactory& rhs) const;

        virtual Qosmetics::Core::SaberModelController* MakeSaber(GlobalNamespace::SaberType saberType) const = 0;
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
#define SABERMODELFACTORY_REGISTRATION(identifier, priority)                                                                                                                             \
    class sabermodelfactory_registration_##identifier_##priority_ : Qosmetics::Core::SaberModelFactoryRegister::SaberModelFactory                                                        \
    {                                                                                                                                                                                    \
        sabermodelfactory_registration_##identifier_##priority_() : Qosmetics::Core::SaberModelFactoryRegister::SaberModelFactory(#identifier, priority);                                \
        {                                                                                                                                                                                \
            Qosmetics::Core::SaberModelFactoryRegister::Register(this);                                                                                                                  \
        }                                                                                                                                                                                \
        Qosmetics::Core::SaberModelController* MakeSaber(GlobalNamespace::SaberType saberType) const override;                                                                           \
    };                                                                                                                                                                                   \
    static sabermodelfactory_registration_##identifier_##priority_ sabermodelfactory_registration_##identifier_##priority_Instance = redecoration_registration_##contract_##priority_(); \
    Qosmetics::Core::SaberModelController* sabermodelfactory_registration_##identifier_##priority_::MakeSaber(GlobalNamespace::SaberType saberType) const
#endif

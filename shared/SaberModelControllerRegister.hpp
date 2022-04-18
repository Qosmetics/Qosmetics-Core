#pragma once
#include "SaberModelController.hpp"

#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/SaberType.hpp"
#include "UnityEngine/Transform.hpp"

#include <type_traits>

namespace Qosmetics::Core::SaberModelControllerRegister
{
    template <typename T>
    concept ModelController = std::is_convertible_v<T, Qosmetics::Core::SaberModelController*> && requires(T a, GlobalNamespace::Saber* saber)
    {
        a->Init(saber);
    };

    class SaberModelControllerRegistration
    {
    public:
        std::string identifier;
        int priority;
        virtual Il2CppReflectionType* get_saberModelControllertype() const = 0;

        SaberModelControllerRegistration(std::string_view identifier, int priority) : identifier(identifier), priority(priority){};

        bool operator<(const SaberModelControllerRegistration& rhs) const;
    };

    /// @brief register a registration to redecorate something
    /// @param registration the registration to use
    void Register(const SaberModelControllerRegistration* registration);
}

#ifndef SABERMODELCONTROLLER_REGISTRATION
/*
macro to be used in a similiar way to a hook, this makes creating registrations far easier than having to manually manage everythinbg, and ensures registrations are used as intended

example usage:
SABERMODELCONTROLLER_REGISTRATION(QosmeticsSabers, 10, Qosmetics::Sabers::SaberModelController*)
*/
#define SABERMODELCONTROLLER_REGISTRATION(identifier, priority, modelControllerType)                                                                                           \
    template <Qosmetics::Core::SaberModelControllerRegister::ModelController T>                                                                                                \
    struct sabermodelcontroller_registration_##identifier##_##priority : Qosmetics::Core::SaberModelControllerRegister::SaberModelControllerRegistration                       \
    {                                                                                                                                                                          \
        sabermodelcontroller_registration_##identifier##_##priority() : Qosmetics::Core::SaberModelControllerRegister::SaberModelControllerRegistration(#identifier, priority) \
        {                                                                                                                                                                      \
            Qosmetics::Core::SaberModelControllerRegister::Register(this);                                                                                                     \
        }                                                                                                                                                                      \
        Il2CppReflectionType* get_saberModelControllertype() const override { return csTypeOf(T); };                                                                           \
    };                                                                                                                                                                         \
    static sabermodelcontroller_registration_##identifier##_##priority<modelControllerType> sabermodelcontroller_registration_##identifier##_##priorityInstance = sabermodelcontroller_registration_##identifier##_##priority<modelControllerType>()
#endif

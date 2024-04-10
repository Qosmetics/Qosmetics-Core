#pragma once

#include "./_config.h"
#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"

namespace Qosmetics::Core::Config
{
    struct QOSMETICS_CORE_EXPORT Registration
    {
        Registration(std::string_view memberName) : memberName(memberName){};
        std::string memberName;

        // Serialize your config values into the passed member, it already will have your memberName so you just have to add to it
        virtual void SaveConfig(rapidjson::Value& member, rapidjson::Document::AllocatorType& allocator) const = 0;
        // Deserialize your config values from the passed member
        virtual bool LoadConfig(const rapidjson::Value& member) const = 0;
        // Method that is ran when the profile is changed in the user profile switcher, this is seperate because config load shouldn't trigger certain things
        virtual void OnProfileSwitched() const = 0;
    };

    QOSMETICS_CORE_EXPORT void Register(const Registration* registration);

    /// @brief Make Qosmetics save it's config for the current user
    QOSMETICS_CORE_EXPORT void SaveConfig();
}

#ifndef QOSMETICS_CONFIG
/// This macro is used to register a subconfig to the global config json value. This is supposed to be used for supporting config profiles
/// example usage:
/// struct SaberPlayerConfigRegistration : public Qosmetics::Core::Config::Registration
/// {
///     void SaveConfig(rapidjson::Value& member, rapidjson::Document::AllocatorType& allocator) const override
///     {
///         /// do stuff here to serialize your config into the passed member
///     }
///
///     bool LoadConfig(const rapidjson::Value& member) const override
///     {
///         /// do stuff here to deserialize your config from the passed member
///     }
///
///     void OnProfileSwitched() const override
///     {
///         /// change the active saber or something idk
///     }
/// };
/// QOSMETICS_CONFIG(SaberPlayerConfigRegistration, "saberConfig");
#define QOSMETICS_CONFIG_REGISTER(typename_, memberName_)                          \
    struct QOSMETICS_CORE_EXPORT config_registration_##typename : public typename_ \
    {                                                                              \
        config_registration_##typename() : typename_(memberName_)                  \
        {                                                                          \
            Qosmetics::Core::Config::Register(this);                               \
        };                                                                         \
    };                                                                             \
    static config_registration_##typename config_registration_##typename##_Instance = config_registration_##typename()
#endif

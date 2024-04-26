#pragma once

#include "../_config.h"
#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"

namespace Qosmetics::Core
{
    class QOSMETICS_CORE_EXPORT BasicConfig
    {
    public:
        BasicConfig(){};
        BasicConfig(const rapidjson::Value& val){};

        virtual rapidjson::Value ToJson(rapidjson::Document::AllocatorType& allocator) = 0;
    };
}

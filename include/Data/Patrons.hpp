#pragma once

#include "web-utils/shared/WebUtils.hpp"
#include <string>
#include <vector>

namespace Qosmetics::Core
{
    struct Patrons
    {
        static Patrons Parse(std::string_view json);

        bool any() const;
        std::vector<std::string> enthusiastic = {};
        std::vector<std::string> amazing = {};
        std::vector<std::string> legendary = {};
        std::vector<std::string> paypal = {};
    };

    struct PatronResponse : public WebUtils::GenericResponse<Patrons>
    {
        virtual bool AcceptData(std::span<uint8_t const> data) override
        {
            std::string_view str{(char*)data.data(), data.size()};
            responseData = Patrons::Parse(str);
            return true;
        }
    };
}

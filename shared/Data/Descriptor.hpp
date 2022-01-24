#pragma once
#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"

#include <string>

namespace Qosmetics::Core
{
    struct DescriptorComparator;
    class Descriptor
    {
    public:
        Descriptor();
        Descriptor(const Descriptor& other);
        Descriptor(const rapidjson::Value& val, std::string_view filePath);
        Descriptor(const rapidjson::Value& val);

        std::string_view get_author() const;
        std::string_view get_name() const;
        std::string_view get_description() const;
        std::string_view get_filePath() const;

    private:
        std::string author = "";
        std::string name = "";
        std::string description = "";
        std::string filePath = "";

        friend DescriptorComparator;
    };

    struct DescriptorComparator
    {
        bool operator()(const Descriptor& lhs, const Descriptor& rhs) const
        {
            return lhs.name < rhs.name;
        }
    };
}
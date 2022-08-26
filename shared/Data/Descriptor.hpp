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
        Descriptor(std::string_view author, std::string_view name, std::string_view description, std::string_view filePath, std::string_view coverImage) : author(author), name(name), description(description), filePath(filePath), coverImage(coverImage){};
        rapidjson::Value ToJson(rapidjson::Document::AllocatorType& allocator) const;

        [[nodiscard]] std::string_view get_author() const;
        [[nodiscard]] std::string_view get_name() const;
        [[nodiscard]] std::string_view get_description() const;
        [[nodiscard]] std::string_view get_filePath() const;
        [[nodiscard]] std::string_view get_coverImage() const;

    private:
        std::string author;
        std::string name;
        std::string description;
        std::string filePath;
        std::string coverImage;

        friend DescriptorComparator;
    };

    struct DescriptorComparator
    {
        constexpr bool operator()(const Descriptor& lhs, const Descriptor& rhs) const
        {
            return lhs.name < rhs.name;
        }
    };
}
#pragma once

#include "../_config.h"
#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"
#include <string>

namespace Qosmetics::Core
{
    struct QOSMETICS_CORE_EXPORT DescriptorComparator;
    class QOSMETICS_CORE_EXPORT Descriptor {
        public:
            Descriptor() = default;
            Descriptor(Descriptor const& other) = default;

            Descriptor(const rapidjson::Value& val, std::string_view filePath);
            Descriptor(const rapidjson::Value& val);
            Descriptor(std::string_view author, std::string_view name, std::string_view description, std::string_view filePath, std::string_view coverImage) : _author(author), _name(name), _description(description), _filePath(filePath), _coverImage(coverImage){};
            rapidjson::Value ToJson(rapidjson::Document::AllocatorType& allocator) const;

            [[nodiscard]] std::string_view get_author() const;
            __declspec(property(get=get_author)) std::string_view author;

            [[nodiscard]] std::string_view get_name() const;
            __declspec(property(get=get_name)) std::string_view name;

            [[nodiscard]] std::string_view get_description() const;
            __declspec(property(get=get_description)) std::string_view description;

            [[nodiscard]] std::string_view get_filePath() const;
            __declspec(property(get=get_filePath)) std::string_view filePath;

            [[nodiscard]] std::string_view get_coverImage() const;
            __declspec(property(get=get_coverImage)) std::string_view coverImage;

        private:
            std::string _author;
            std::string _name;
            std::string _description;
            std::string _filePath;
            std::string _coverImage;
    };

    struct QOSMETICS_CORE_EXPORT DescriptorComparator
    {
        constexpr bool operator()(const Descriptor& lhs, const Descriptor& rhs) const
        {
            return lhs.name < rhs.name;
        }
    };
}

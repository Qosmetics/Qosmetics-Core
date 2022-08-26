#include "Data/Descriptor.hpp"

namespace Qosmetics::Core
{
    Descriptor::Descriptor(){};

    Descriptor::Descriptor(const Descriptor& other) : name(other.name), author(other.author), description(other.description), filePath(other.filePath), coverImage(other.coverImage){};

    Descriptor::Descriptor(const rapidjson::Value& val, std::string_view filePath) : filePath(filePath)
    {
        name = val["objectName"].GetString();
        author = val["author"].GetString();
        description = val["description"].GetString();
        auto coverImageItr = val.FindMember("coverImage");
        if (coverImageItr != val.MemberEnd())
        {
            coverImage = coverImageItr->value.GetString();
        }
    }

    Descriptor::Descriptor(const rapidjson::Value& val) : filePath("")
    {
        name = val["objectName"].GetString();
        author = val["author"].GetString();
        description = val["description"].GetString();
        auto coverImageItr = val.FindMember("coverImage");
        if (coverImageItr != val.MemberEnd())
        {
            coverImage = coverImageItr->value.GetString();
        }
    }

    rapidjson::Value Descriptor::ToJson(rapidjson::Document::AllocatorType& allocator) const
    {
        rapidjson::Value val;
        val.SetObject();
        val.AddMember("author", rapidjson::Value(author.c_str(), author.size(), allocator), allocator);
        val.AddMember("objectName", rapidjson::Value(name.c_str(), name.size(), allocator), allocator);
        val.AddMember("description", rapidjson::Value(description.c_str(), description.size(), allocator), allocator);
        val.AddMember("coverImage", rapidjson::Value(coverImage.c_str(), coverImage.size(), allocator), allocator);
        return val;
    }

    std::string_view Descriptor::get_author() const { return author; }
    std::string_view Descriptor::get_name() const { return name; }
    std::string_view Descriptor::get_description() const { return description; }
    std::string_view Descriptor::get_filePath() const { return filePath; }
    std::string_view Descriptor::get_coverImage() const { return coverImage; }

}
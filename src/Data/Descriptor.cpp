#include "Data/Descriptor.hpp"
#include <string>

static std::optional<std::string> get_string_opt(rapidjson::Value const& val, std::string key) {
    auto itr  = val.FindMember(key);
    if (itr == val.MemberEnd()) return std::nullopt;
    return itr->value.Get<std::string>();
}

namespace Qosmetics::Core {
    Descriptor::Descriptor(const rapidjson::Value& val, std::string_view filePath) :
        _filePath(filePath),
        _name(val["objectName"].Get<std::string>()),
        _author(val["author"].Get<std::string>()),
        _description(val["description"].Get<std::string>()),
        _coverImage(get_string_opt(val, "coverImage").value_or(""))
    {}

    Descriptor::Descriptor(const rapidjson::Value& val) : Descriptor(val, "") {}

    rapidjson::Value Descriptor::ToJson(rapidjson::Document::AllocatorType& allocator) const {
        rapidjson::Value val;
        val.SetObject();
        val.AddMember("author", rapidjson::Value(_author.c_str(), _author.size(), allocator), allocator);
        val.AddMember("objectName", rapidjson::Value(_name.c_str(), _name.size(), allocator), allocator);
        val.AddMember("description", rapidjson::Value(_description.c_str(), _description.size(), allocator), allocator);
        val.AddMember("coverImage", rapidjson::Value(_coverImage.c_str(), _coverImage.size(), allocator), allocator);
        return val;
    }

    std::string_view Descriptor::get_author() const { return _author; }
    std::string_view Descriptor::get_name() const { return _name; }
    std::string_view Descriptor::get_description() const { return _description; }
    std::string_view Descriptor::get_filePath() const { return _filePath; }
    std::string_view Descriptor::get_coverImage() const { return _coverImage; }
}

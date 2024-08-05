#include "Data/Patrons.hpp"
#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"
#include "logging.hpp"

void get_string_vector(rapidjson::Document const& doc, std::string identifier, std::vector<std::string>& out) {
    auto memberItr = doc.FindMember(identifier);
    if (memberItr != doc.MemberEnd()) {
        for (auto& name : memberItr->value.GetArray()) {
            out.emplace_back(name.GetString(), name.GetStringLength());
            INFO("Found {}", out.back());
        }
    } else {
        ERROR("Couldn't find member {} in doc", identifier);
    }
}

namespace Qosmetics::Core {
    Patrons Patrons::Parse(std::string_view json){
        rapidjson::Document doc;
        doc.Parse(json.data(), json.size());
        auto result = Patrons();
        if (doc.GetParseError() == 0) {
            get_string_vector(doc, "enthusiastic", result.enthusiastic);
            get_string_vector(doc, "amazing", result.amazing);
            get_string_vector(doc, "legendary", result.legendary);
            get_string_vector(doc, "paypal", result.paypal);
        } else {
            ERROR("Doc parse Error {}, data:\n{}", (int)doc.GetParseError(), json);
        }

        return result;
    }

    bool Patrons::any() const {
        // if any is not empty, return true
        return !enthusiastic.empty() || !amazing.empty() || !legendary.empty() || !paypal.empty();
    }
}

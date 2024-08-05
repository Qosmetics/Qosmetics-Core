#include "Data/Creators.hpp"
#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"
#include "logging.hpp"

#include "web-utils/shared/WebUtils.hpp"
#include "bsml/shared/BSML/MainThreadScheduler.hpp"
#include "static-defines.hpp"
#include <unordered_map>


UnityEngine::Color FromJson(const rapidjson::Value& v) {
    return {v["R"].Get<float>(), v["G"].Get<float>(), v["B"].Get<float>(), 1.0f};
}

namespace Qosmetics::Core::Creators {
    UnityEngine::Color defaultColor = {0.8f, 0.8f, 0.8f, 1.0f};
    std::unordered_map<std::string, UnityEngine::Color> creatorToColorMap = {
        {"RedBrumbler", {1.0f, 1.0f, 1.0f, 1.0f}},
        {"Bobbie", {1.0f, 1.0f, 1.0f, 1.0f}}
    };

    void ParseCreators(rapidjson::Document const& doc) {
        auto memberEnd = doc.MemberEnd();
        for (auto itr = doc.MemberBegin(); itr != memberEnd; itr++) {
            auto& val = itr->value;
            creatorToColorMap[itr->name.Get<std::string>()] = FromJson(val);
        }
    }

    void ParseCreators(std::string_view str) {
        rapidjson::Document doc;
        doc.Parse(str.data(), str.size());
        ParseCreators(doc);
    }

    UnityEngine::Color GetCreatorColor(std::string creator) {
        auto colorItr = creatorToColorMap.find(creator);
        if (colorItr == creatorToColorMap.end())
            return defaultColor;
        return colorItr->second;
    }

    void TryDownloadCreators() {
        std::shared_future fut = WebUtils::GetAsync<WebUtils::JsonResponse>({creator_color_url});
        BSML::MainThreadScheduler::AwaitFuture<WebUtils::JsonResponse>(
            fut,
            [fut]() -> void
            {
                auto& response = fut.get();
                if (response.IsSuccessful() && response.DataParsedSuccessful())
                    Qosmetics::Core::Creators::ParseCreators(response.responseData.value());
                else
                    ERROR("Could not download creators json");
            });
    }
}

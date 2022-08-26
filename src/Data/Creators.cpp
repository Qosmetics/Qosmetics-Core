#include "Data/Creators.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "static-defines.hpp"
#include <unordered_map>

#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "UnityEngine/Networking/DownloadHandler.hpp"
#include "UnityEngine/Networking/UnityWebRequest.hpp"

#include "logging.hpp"

UnityEngine::Color FromJson(const rapidjson::Value& v)
{
    return {v["R"].GetFloat(), v["G"].GetFloat(), v["B"].GetFloat(), 1.0f};
}

namespace Qosmetics::Core::Creators
{
    UnityEngine::Color defaultColor = {0.8f, 0.8f, 0.8f, 1.0f};
    std::unordered_map<std::string, UnityEngine::Color> creatorToColorMap = {
        {"RedBrumbler", {1.0f, 1.0f, 1.0f, 1.0f}},
        {"Bobbie", {1.0f, 1.0f, 1.0f, 1.0f}}};

    void ParseCreators(const rapidjson::Document& doc)
    {
        for (rapidjson::Value::ConstMemberIterator i = doc.MemberBegin(); i != doc.MemberEnd(); ++i)
        {
            const rapidjson::Value& val = i->value;
            creatorToColorMap[std::string(i->name.GetString())] = FromJson(val);
        }
    }

    UnityEngine::Color GetCreatorColor(std::string creator)
    {
        auto colorItr = creatorToColorMap.find(creator);
        if (colorItr == creatorToColorMap.end())
            return defaultColor;
        return colorItr->second;
    }

    custom_types::Helpers::Coroutine DownloadCreatorColors()
    {
        UnityEngine::Networking::UnityWebRequest* www = UnityEngine::Networking::UnityWebRequest::Get(creator_color_url);
        co_yield reinterpret_cast<System::Collections::IEnumerator*>(www->SendWebRequest());

        bool isHttpError = www->get_isHttpError();
        bool isNetworkError = www->get_isNetworkError();

        if (isHttpError || isNetworkError)
        {
            ERROR("Failed to fetch creators file from resources repository");
            ERROR("Was http error: {}", isHttpError);
            ERROR("Was network error: {}", isNetworkError);

            co_return;
        }
        auto downloadHandler = www->get_downloadHandler();

        rapidjson::Document d;
        d.Parse(static_cast<std::string>(downloadHandler->get_text()));

        if (d.GetParseError() == 0)
            ParseCreators(d);

        co_return;
    }

    void Download()
    {
        GlobalNamespace::SharedCoroutineStarter::get_instance()->StartCoroutine(custom_types::Helpers::CoroutineHelper::New(DownloadCreatorColors()));
    }
}
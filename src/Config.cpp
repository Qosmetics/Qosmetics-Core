#include "ConfigRegister.hpp"
#include "ConfigRegister_Internal.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "logging.hpp"
#include "static-defines.hpp"

extern modloader::ModInfo modInfo;

Configuration& get_config() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

namespace Qosmetics::Core::Config {
    Config config;

    std::vector<const Registration*> registrations = {};
    void Register(const Registration* registration) {
        registrations.push_back(registration);
    }

    bool LoadConfig() {
        auto& cfg = get_config().config;
        auto lastUsedConfigItr = cfg.FindMember("lastUsedConfig");
        bool foundEverything = true;
        if (lastUsedConfigItr == cfg.MemberEnd())
            foundEverything = false;
        else
            config.lastUsedConfig = lastUsedConfigItr->value.GetString();

        if (!LoadSpecificConfig(config.lastUsedConfig))
            foundEverything = false;

        return foundEverything;
    }

    bool LoadSpecificConfig(std::string_view name) {
        bool foundEverything = true;
        std::string configPath = fmt::format("{}/{}.json", userconfig_path, name);
        INFO("Loading specific config from path {}", configPath);

        if (!fileexists(configPath)) {
            SaveSpecificConfig(name);
            return false;
        }

        std::string content = readfile(configPath);
        rapidjson::Document doc;
        doc.Parse(content);
        if (doc.GetParseError() != 0) {
            ERROR("Doc failed to parse config file, error code: {}", (int)doc.GetParseError());
            return false;
        }

        DEBUG("Had {} config registrations:", registrations.size());
        for (auto* reg : registrations) {
            DEBUG("loading {}", reg->memberName);
            auto valItr = doc.FindMember(reg->memberName);
            // if member not found or couldn't properly load config, something failed
            if (valItr == doc.MemberEnd() || !reg->LoadConfig(valItr->value))
                foundEverything = false;
        }
        return foundEverything;
    }

    void SaveConfig() {
        mkpath(userconfig_path);
        auto& cfg = get_config().config;

        cfg.RemoveAllMembers();
        cfg.SetObject();
        cfg.AddMember("lastUsedConfig", config.lastUsedConfig, cfg.GetAllocator());
        get_config().Write();

        SaveSpecificConfig(config.lastUsedConfig);
    }

    void SaveSpecificConfig(std::string_view name) {
        std::string configPath = fmt::format("{}/{}.json", userconfig_path, name);
        rapidjson::Document doc;
        doc.SetObject();
        if (fileexists(configPath)) {
            std::string content = readfile(configPath);
            doc.Parse(content);
        }

        rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
        DEBUG("Had {} config registrations:", registrations.size());
        for (auto* reg : registrations) {
            DEBUG("saving {}", reg->memberName);
            auto memberItr = doc.FindMember(reg->memberName);
            if (memberItr == doc.MemberEnd()) {
                // didn't already exist, make it and save on that
                rapidjson::Value val;
                val.SetObject();
                reg->SaveConfig(val, allocator);
                doc.AddMember(rapidjson::Value(reg->memberName.c_str(), reg->memberName.length(), allocator), val, allocator);
            } else {
                reg->SaveConfig(memberItr->value, allocator);
            }
        }

        rapidjson::StringBuffer buffer;
        buffer.Clear();
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);
        std::string json(buffer.GetString(), buffer.GetSize());
        writefile(configPath, json);
    }

    void OnProfileSwitched() {
        for (auto* reg : registrations) {
            reg->OnProfileSwitched();
        }
    }
}

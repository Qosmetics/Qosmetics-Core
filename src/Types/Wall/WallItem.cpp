#include "Types/Wall/WallItem.hpp"
#include "QosmeticsLogger.hpp"

#define INFO(value...) QosmeticsLogger::GetContextLogger("Wall Item").info(value)
#define ERROR(value...) QosmeticsLogger::GetContextLogger("Wall Item").error(value)

namespace Qosmetics
{
    void WallItem::ConfigCallback(UnityEngine::TextAsset* textAsset)
    {
        if (!textAsset)
        {
            ERROR("Config was nullptr! did someone fuck with the exporter, or is the read broken? regardless keeping Default config");
            return;
        }

        Il2CppString* descriptorstring = textAsset->get_text();
        
        std::string json = to_utf8(csstrtostr(descriptorstring));

        rapidjson::Document d;
        d.Parse(json.c_str());

        config = WallConfig(d);
        ConfigLoaded = true;
    }
}

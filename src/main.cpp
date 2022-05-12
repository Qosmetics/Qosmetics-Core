#include "UI/GameplaySetupView.hpp"
#include "assets.hpp"
#include "custom-types/shared/register.hpp"
#include "hooks.hpp"
#include "logging.hpp"
#include "modloader/shared/modloader.hpp"
#include "questui/shared/QuestUI.hpp"

#include "HMUI/CurvedTextMeshPro.hpp"
#include "HMUI/ImageView.hpp"

#include "ConfigRegister_Internal.hpp"
#include "diglett/shared/Conversions.hpp"
#include "diglett/shared/Register.hpp"

#include <fmt/format.h>

ModInfo modInfo = {MOD_ID, VERSION};

extern "C" void setup(ModInfo& info)
{
    info = modInfo;
}

extern "C" void load()
{
    if (!Qosmetics::Core::Config::LoadConfig())
        Qosmetics::Core::Config::SaveConfig();
    il2cpp_functions::Class_Init(classof(HMUI::ImageView*));
    il2cpp_functions::Class_Init(classof(HMUI::CurvedTextMeshPro*));

    auto& logger = Qosmetics::Core::Logging::getLogger();
    Hooks::InstallHooks(logger);
    custom_types::Register::AutoRegister();

    QuestUI::Register::RegisterGameplaySetupMenu<Qosmetics::Core::GameplaySetupView*>(modInfo, "Qosmetics");

    Diglett::RegisterAsset(ASSET_TO_STR(de_xml), Diglett::Language::GERMAN);
    Diglett::RegisterAsset(ASSET_TO_STR(en_xml), Diglett::Language::ENGLISH);
    Diglett::RegisterAsset(ASSET_TO_STR(es_xml), Diglett::Language::SPANISH);
    Diglett::RegisterAsset(ASSET_TO_STR(fr_xml), Diglett::Language::FRENCH);
    Diglett::RegisterAsset(ASSET_TO_STR(ja_xml), Diglett::Language::JAPANESE);
    Diglett::RegisterAsset(ASSET_TO_STR(ko_xml), Diglett::Language::KOREAN);

    if (!Paper::Logger::IsInited())
    {
        mkpath("/sdcard/Android/data/com.beatgames.beatsaber/files/logs/paper");
        Paper::Logger::Init("/sdcard/Android/data/com.beatgames.beatsaber/files/logs/paper");
    }

    srand(time(NULL));

    INFO("Boats and hoes");
}
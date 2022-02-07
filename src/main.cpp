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
#include "diglett/shared/Register.hpp"
ModInfo modInfo = {ID, VERSION};

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

    Diglett::Register::RegisterLocales<Diglett::Languages::German>(logger, ASSET_TO_XML(de_xml));
    Diglett::Register::RegisterLocales<Diglett::Languages::English>(logger, ASSET_TO_XML(en_xml));
    Diglett::Register::RegisterLocales<Diglett::Languages::Spanish>(logger, ASSET_TO_XML(es_xml));
    Diglett::Register::RegisterLocales<Diglett::Languages::French>(logger, ASSET_TO_XML(fr_xml));
    Diglett::Register::RegisterLocales<Diglett::Languages::Japanese>(logger, ASSET_TO_XML(ja_xml));
    Diglett::Register::RegisterLocales<Diglett::Languages::Korean>(logger, ASSET_TO_XML(ko_xml));
}
//#include "UI/GameplaySetupView.hpp"
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

#include "Installers/MenuInstaller.hpp"
#include "lapiz/shared/zenject/Zenjector.hpp"

ModInfo modInfo = {MOD_ID, VERSION};

extern "C" void setup(ModInfo& info)
{
    info = modInfo;
}

extern "C" void load()
{
    if (!Qosmetics::Core::Config::LoadConfig())
        Qosmetics::Core::Config::SaveConfig();
    il2cpp_functions::Init();

    auto& logger = Qosmetics::Core::Logging::getLogger();
    Hooks::InstallHooks(logger);
    custom_types::Register::AutoRegister();

    // QuestUI::Register::RegisterGameplaySetupMenu<Qosmetics::Core::GameplaySetupView*>(modInfo, "Qosmetics");

    auto zenjector = ::Lapiz::Zenject::Zenjector::Get();
    zenjector->Install<Qosmetics::Core::MenuInstaller*>(::Lapiz::Zenject::Location::Menu);

    Diglett::RegisterAsset(static_cast<std::string_view>(IncludedAssets::de_xml), Diglett::Language::GERMAN);
    Diglett::RegisterAsset(static_cast<std::string_view>(IncludedAssets::en_xml), Diglett::Language::ENGLISH);
    Diglett::RegisterAsset(static_cast<std::string_view>(IncludedAssets::es_xml), Diglett::Language::SPANISH);
    Diglett::RegisterAsset(static_cast<std::string_view>(IncludedAssets::fr_xml), Diglett::Language::FRENCH);
    Diglett::RegisterAsset(static_cast<std::string_view>(IncludedAssets::ja_xml), Diglett::Language::JAPANESE);
    Diglett::RegisterAsset(static_cast<std::string_view>(IncludedAssets::ko_xml), Diglett::Language::KOREAN);

    srand(time(NULL));

    INFO("Boats and hoes");
}
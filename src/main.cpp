// #include "UI/GameplaySetupView.hpp"
#include "_config.h"
#include "assets.hpp"
#include "custom-types/shared/register.hpp"
#include "hooks.hpp"
#include "logging.hpp"
#include "scotland2/shared/modloader.h"
#include "static-defines.hpp"

#include "HMUI/CurvedTextMeshPro.hpp"
#include "HMUI/ImageView.hpp"

#include "ConfigRegister_Internal.hpp"

#include <fmt/format.h>

#include "Installers/MenuInstaller.hpp"
#include "bsml/shared/BSMLDataCache.hpp"
#include "lapiz/shared/AttributeRegistration.hpp"
#include "lapiz/shared/zenject/Zenjector.hpp"

#include "Data/Creators.hpp"
#include "Data/Patrons.hpp"

modloader::ModInfo modInfo = {MOD_ID, VERSION, 0};

QOSMETICS_CORE_EXPORT_FUNC void setup(CModInfo* info)
{
    info->id = MOD_ID;
    info->version = VERSION;
    info->version_long = 0;
}

QOSMETICS_CORE_EXPORT_FUNC void late_load()
{
    INFO("Loading Qosmetics");

    il2cpp_functions::Init();
    if (!Qosmetics::Core::Config::LoadConfig())
        Qosmetics::Core::Config::SaveConfig();

    Hooks::InstallHooks();
    custom_types::Register::AutoRegister();
    Lapiz::Attributes::AutoRegister();

    auto zenjector = ::Lapiz::Zenject::Zenjector::Get();
    zenjector->Install<Qosmetics::Core::MenuInstaller*>(::Lapiz::Zenject::Location::Menu);

    Qosmetics::Core::Creators::TryDownloadCreators();

    srand(time(NULL));
}

BSML_DATACACHE(deleteIcon)
{
    return Assets::Icons::DeleteIcon_png;
}

BSML_DATACACHE(placeHolderIcon)
{
    return Assets::Icons::PlaceHolderImage_png;
}

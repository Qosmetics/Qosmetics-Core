//#include "UI/GameplaySetupView.hpp"
#include "assets.hpp"
#include "custom-types/shared/register.hpp"
#include "hooks.hpp"
#include "logging.hpp"
#include "modloader/shared/modloader.hpp"

#include "HMUI/CurvedTextMeshPro.hpp"
#include "HMUI/ImageView.hpp"

#include "ConfigRegister_Internal.hpp"

#include <fmt/format.h>

#include "Installers/MenuInstaller.hpp"
#include "bsml/shared/BSMLDataCache.hpp"
#include "lapiz/shared/zenject/Zenjector.hpp"

ModInfo modInfo = {MOD_ID, VERSION};

extern "C" void setup(ModInfo& info)
{
    info = modInfo;
}

extern "C" void load()
{
    il2cpp_functions::Init();
    if (!Qosmetics::Core::Config::LoadConfig())
        Qosmetics::Core::Config::SaveConfig();

    auto& logger = Qosmetics::Core::Logging::getLogger();
    Hooks::InstallHooks(logger);
    custom_types::Register::AutoRegister();

    auto zenjector = ::Lapiz::Zenject::Zenjector::Get();
    zenjector->Install<Qosmetics::Core::MenuInstaller*>(::Lapiz::Zenject::Location::Menu);

    srand(time(NULL));

    INFO("Boats and hoes");
}

BSML_DATACACHE(deleteIcon)
{
    return IncludedAssets::DeleteIcon_png;
}

BSML_DATACACHE(placeHolderIcon)
{
    return IncludedAssets::PlaceHolderImage_png;
}

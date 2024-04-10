#pragma once

#include "Zenject/Installer.hpp"
#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Core, MenuInstaller, ::Zenject::Installer,
                      DECLARE_DEFAULT_CTOR();
                      DECLARE_OVERRIDE_METHOD_MATCH(void, InstallBindings, &::Zenject::Installer::InstallBindings);

)

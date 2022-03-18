#include "Redecoration.hpp"
#include "RedecorationMacros.hpp"
#include "hooks.hpp"
#include "logging.hpp"

#include "GlobalNamespace/BoolSO.hpp"
#include "GlobalNamespace/EffectPoolsManualInstaller.hpp"
#include "GlobalNamespace/NoteDebris.hpp"

#include "Zenject/DiContainer.hpp"

MAKE_AUTO_HOOK_ORIG_MATCH(EffectPoolsManualInstaller_ManualInstallBindings, &GlobalNamespace::EffectPoolsManualInstaller::ManualInstallBindings, void, GlobalNamespace::EffectPoolsManualInstaller* self, Zenject::DiContainer* container, bool shortBeatEffect)
{
    EffectPoolsManualInstaller_ManualInstallBindings(self, container, shortBeatEffect);
}

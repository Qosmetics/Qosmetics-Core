#include "Redecoration.hpp"
#include "RedecorationMacros.hpp"
#include "hooks.hpp"
#include "logging.hpp"

#include "GlobalNamespace/BoolSO.hpp"
#include "GlobalNamespace/EffectPoolsManualInstaller.hpp"
#include "GlobalNamespace/NoteDebris.hpp"

#include "Zenject/Dicontainer.hpp"

MAKE_AUTO_HOOK_ORIG_MATCH(EffectPoolsManualInstaller_ManualInstallBindings, &GlobalNamespace::EffectPoolsManualInstaller::ManualInstallBindings, void, GlobalNamespace::EffectPoolsManualInstaller* self, Zenject::DiContainer* container, bool shortBeatEffect)
{
    auto noteDebrisHDPrefab = self->dyn__noteDebrisHDPrefab();
    auto noteDebrisLWPrefab = self->dyn__noteDebrisLWPrefab();
    bool hd = self->dyn__noteDebrisHDConditionVariable()->get_value();
    static auto self_type = il2cpp_utils::GetSystemType(il2cpp_utils::ExtractType(self->klass));
    if (hd)
    {
        MAKE_CLONE_AND_PARENT(noteDebrisHDPrefab);
        REDECORATE(noteDebrisHDPrefab);
        EffectPoolsManualInstaller_ManualInstallBindings(self, container, shortBeatEffect);
        self->dyn__noteDebrisLWPrefab() = noteDebrisLWPrefab;
    }
    else
    {
        MAKE_CLONE_AND_PARENT(noteDebrisLWPrefab);
        REDECORATE(noteDebrisLWPrefab);
        EffectPoolsManualInstaller_ManualInstallBindings(self, container, shortBeatEffect);
        self->dyn__noteDebrisLWPrefab() = noteDebrisLWPrefab;
    }
}

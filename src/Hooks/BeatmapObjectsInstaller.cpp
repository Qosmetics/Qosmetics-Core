#include "Redecoration.hpp"
#include "RedecorationMacros.hpp"
#include "hooks.hpp"
#include "logging.hpp"

#include "GlobalNamespace/BeatmapObjectsInstaller.hpp"
#include "GlobalNamespace/BombNoteController.hpp"
#include "GlobalNamespace/GameNoteController.hpp"
#include "GlobalNamespace/ObstacleController.hpp"

MAKE_AUTO_HOOK_ORIG_MATCH(BeatmapObjectsInstaller_InstallBindings, &GlobalNamespace::BeatmapObjectsInstaller::InstallBindings, void, GlobalNamespace::BeatmapObjectsInstaller* self)
{
    auto normalBasicNotePrefab = self->dyn__normalBasicNotePrefab();
    auto proModeNotePrefab = self->dyn__proModeNotePrefab();
    auto bombNotePrefab = self->dyn__bombNotePrefab();
    auto obstaclePrefab = self->dyn__obstaclePrefab();

    MAKE_CLONE_AND_PARENT(normalBasicNotePrefab);
    MAKE_CLONE_AND_PARENT(proModeNotePrefab);
    MAKE_CLONE_AND_PARENT(bombNotePrefab);
    MAKE_CLONE_AND_PARENT(obstaclePrefab);

    static auto self_type = il2cpp_utils::GetSystemType(il2cpp_utils::ExtractType(self->klass));
    REDECORATE(normalBasicNotePrefab);
    REDECORATE(proModeNotePrefab);
    REDECORATE(bombNotePrefab);
    REDECORATE(obstaclePrefab);

    BeatmapObjectsInstaller_InstallBindings(self);

    self->dyn__normalBasicNotePrefab() = normalBasicNotePrefab;
    self->dyn__proModeNotePrefab() = proModeNotePrefab;
    self->dyn__bombNotePrefab() = bombNotePrefab;
    self->dyn__obstaclePrefab() = obstaclePrefab;
}

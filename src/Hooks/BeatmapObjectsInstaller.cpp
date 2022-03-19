#include "Redecoration.hpp"
#include "RedecorationMacros.hpp"
#include "hooks.hpp"
#include "logging.hpp"

#include "GlobalNamespace/BeatmapObjectsInstaller.hpp"
#include "GlobalNamespace/BombNoteController.hpp"
#include "GlobalNamespace/BurstSliderGameNoteController.hpp"
#include "GlobalNamespace/GameNoteController.hpp"
#include "GlobalNamespace/ObstacleController.hpp"

MAKE_AUTO_HOOK_ORIG_MATCH(BeatmapObjectsInstaller_InstallBindings, &GlobalNamespace::BeatmapObjectsInstaller::InstallBindings, void, GlobalNamespace::BeatmapObjectsInstaller* self)
{
    auto normalBasicNotePrefab = self->dyn__normalBasicNotePrefab();
    auto proModeNotePrefab = self->dyn__proModeNotePrefab();
    auto burstSliderHeadNotePrefab = self->dyn__burstSliderHeadNotePrefab();
    auto burstSliderNotePrefab = self->dyn__burstSliderNotePrefab();
    auto burstSliderFillPrefab = self->dyn__burstSliderFillPrefab();
    auto bombNotePrefab = self->dyn__bombNotePrefab();
    auto obstaclePrefab = self->dyn__obstaclePrefab();

    MAKE_CLONE_AND_PARENT(normalBasicNotePrefab);
    MAKE_CLONE_AND_PARENT(proModeNotePrefab);
    MAKE_CLONE_AND_PARENT(burstSliderHeadNotePrefab);
    MAKE_CLONE_AND_PARENT(burstSliderNotePrefab);
    MAKE_CLONE_AND_PARENT(burstSliderFillPrefab);
    MAKE_CLONE_AND_PARENT(bombNotePrefab);
    MAKE_CLONE_AND_PARENT(obstaclePrefab);

    static auto self_type = il2cpp_utils::GetSystemType(il2cpp_utils::ExtractType(self->klass));
    auto container = self->get_Container();
    REDECORATE(normalBasicNotePrefab);
    REDECORATE(proModeNotePrefab);
    REDECORATE(burstSliderHeadNotePrefab);
    REDECORATE(burstSliderNotePrefab);
    REDECORATE(burstSliderFillPrefab);
    REDECORATE(bombNotePrefab);
    REDECORATE(obstaclePrefab);

    BeatmapObjectsInstaller_InstallBindings(self);

    self->dyn__normalBasicNotePrefab() = normalBasicNotePrefab;
    self->dyn__proModeNotePrefab() = proModeNotePrefab;
    self->dyn__burstSliderHeadNotePrefab() = burstSliderHeadNotePrefab;
    self->dyn__burstSliderNotePrefab() = burstSliderNotePrefab;
    self->dyn__burstSliderFillPrefab() = burstSliderFillPrefab;
    self->dyn__bombNotePrefab() = bombNotePrefab;
    self->dyn__obstaclePrefab() = obstaclePrefab;
}

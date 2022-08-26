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
    auto normalBasicNotePrefab = self->normalBasicNotePrefab;
    auto proModeNotePrefab = self->proModeNotePrefab;
    auto burstSliderHeadNotePrefab = self->burstSliderHeadNotePrefab;
    auto burstSliderNotePrefab = self->burstSliderNotePrefab;
    auto burstSliderFillPrefab = self->burstSliderFillPrefab;
    auto bombNotePrefab = self->bombNotePrefab;
    auto obstaclePrefab = self->obstaclePrefab;

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

    self->normalBasicNotePrefab = normalBasicNotePrefab;
    self->proModeNotePrefab = proModeNotePrefab;
    self->burstSliderHeadNotePrefab = burstSliderHeadNotePrefab;
    self->burstSliderNotePrefab = burstSliderNotePrefab;
    self->burstSliderFillPrefab = burstSliderFillPrefab;
    self->bombNotePrefab = bombNotePrefab;
    self->obstaclePrefab = obstaclePrefab;
}

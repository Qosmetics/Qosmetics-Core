#include "Redecoration.hpp"
#include "RedecorationMacros.hpp"
#include "hooks.hpp"
#include "logging.hpp"

#include "GlobalNamespace/FakeMirrorObjectsInstaller.hpp"
#include "GlobalNamespace/MirroredBombNoteController.hpp"
#include "GlobalNamespace/MirroredGameNoteController.hpp"
#include "GlobalNamespace/MirroredObstacleController.hpp"
#include "GlobalNamespace/MirroredSliderController.hpp"

MAKE_AUTO_HOOK_ORIG_MATCH(FakeMirrorObjectsInstaller_InstallBindings, &GlobalNamespace::FakeMirrorObjectsInstaller::InstallBindings, void, GlobalNamespace::FakeMirrorObjectsInstaller* self)
{
    auto mirroredGameNoteControllerPrefab = self->dyn__mirroredGameNoteControllerPrefab();
    auto mirroredBurstSliderHeadGameNoteControllerPrefab = self->dyn__mirroredBurstSliderHeadGameNoteControllerPrefab();
    auto mirroredBurstSliderGameNoteControllerPrefab = self->dyn__mirroredBurstSliderGameNoteControllerPrefab();
    auto mirroredBombNoteControllerPrefab = self->dyn__mirroredBombNoteControllerPrefab();
    auto mirroredObstacleControllerPrefab = self->dyn__mirroredObstacleControllerPrefab();

    MAKE_CLONE_AND_PARENT(mirroredGameNoteControllerPrefab);
    MAKE_CLONE_AND_PARENT(mirroredBurstSliderHeadGameNoteControllerPrefab);
    MAKE_CLONE_AND_PARENT(mirroredBurstSliderGameNoteControllerPrefab);
    MAKE_CLONE_AND_PARENT(mirroredBombNoteControllerPrefab);
    MAKE_CLONE_AND_PARENT(mirroredObstacleControllerPrefab);

    static auto self_type = il2cpp_utils::GetSystemType(il2cpp_utils::ExtractType(self->klass));
    auto container = self->get_Container();
    REDECORATE(mirroredGameNoteControllerPrefab);
    REDECORATE(mirroredBurstSliderHeadGameNoteControllerPrefab);
    REDECORATE(mirroredBurstSliderGameNoteControllerPrefab);
    REDECORATE(mirroredBombNoteControllerPrefab);
    REDECORATE(mirroredObstacleControllerPrefab);

    FakeMirrorObjectsInstaller_InstallBindings(self);

    self->dyn__mirroredGameNoteControllerPrefab() = mirroredGameNoteControllerPrefab;
    self->dyn__mirroredBurstSliderHeadGameNoteControllerPrefab() = mirroredBurstSliderHeadGameNoteControllerPrefab;
    self->dyn__mirroredBurstSliderGameNoteControllerPrefab() = mirroredBurstSliderGameNoteControllerPrefab;
    self->dyn__mirroredBombNoteControllerPrefab() = mirroredBombNoteControllerPrefab;
    self->dyn__mirroredObstacleControllerPrefab() = mirroredObstacleControllerPrefab;
}
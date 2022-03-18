#include "Redecoration.hpp"
#include "RedecorationMacros.hpp"
#include "hooks.hpp"
#include "logging.hpp"

#include "GlobalNamespace/BoolSO.hpp"
#include "GlobalNamespace/NoteDebris.hpp"
#include "GlobalNamespace/NoteDebrisPoolInstaller.hpp"

#include "Zenject/DiContainer.hpp"

MAKE_AUTO_HOOK_ORIG_MATCH(NoteDebrisPoolInstaller_InstallBindings, &GlobalNamespace::NoteDebrisPoolInstaller::InstallBindings, void, GlobalNamespace::NoteDebrisPoolInstaller* self)
{
    auto normalNoteDebrisHDPrefab = self->dyn__normalNoteDebrisHDPrefab();
    auto normalNoteDebrisLWPrefab = self->dyn__normalNoteDebrisLWPrefab();
    auto burstSliderHeadNoteDebrisHDPrefab = self->dyn__burstSliderHeadNoteDebrisHDPrefab();
    auto burstSliderHeadNoteDebrisLWPrefab = self->dyn__burstSliderHeadNoteDebrisLWPrefab();
    auto burstSliderElementNoteHDPrefab = self->dyn__burstSliderElementNoteHDPrefab();
    auto burstSliderElementNoteLWPrefab = self->dyn__burstSliderElementNoteLWPrefab();

    bool hd = self->dyn__noteDebrisHDConditionVariable()->get_value();
    auto container = self->dyn__container();
    static auto self_type = il2cpp_utils::GetSystemType(il2cpp_utils::ExtractType(self->klass));
    if (hd)
    {
        MAKE_CLONE_AND_PARENT(normalNoteDebrisHDPrefab);
        MAKE_CLONE_AND_PARENT(burstSliderHeadNoteDebrisHDPrefab);
        MAKE_CLONE_AND_PARENT(burstSliderElementNoteHDPrefab);
        REDECORATE(normalNoteDebrisHDPrefab);
        REDECORATE(burstSliderHeadNoteDebrisHDPrefab);
        REDECORATE(burstSliderElementNoteHDPrefab);
        NoteDebrisPoolInstaller_InstallBindings(self);
        self->dyn__normalNoteDebrisHDPrefab() = normalNoteDebrisHDPrefab;
        self->dyn__burstSliderHeadNoteDebrisHDPrefab() = burstSliderHeadNoteDebrisHDPrefab;
        self->dyn__burstSliderElementNoteHDPrefab() = burstSliderElementNoteHDPrefab;
    }
    else
    {
        MAKE_CLONE_AND_PARENT(normalNoteDebrisLWPrefab);
        MAKE_CLONE_AND_PARENT(burstSliderHeadNoteDebrisLWPrefab);
        MAKE_CLONE_AND_PARENT(burstSliderElementNoteLWPrefab);
        REDECORATE(normalNoteDebrisLWPrefab);
        REDECORATE(burstSliderHeadNoteDebrisLWPrefab);
        REDECORATE(burstSliderElementNoteLWPrefab);
        NoteDebrisPoolInstaller_InstallBindings(self);
        self->dyn__normalNoteDebrisLWPrefab() = normalNoteDebrisLWPrefab;
        self->dyn__burstSliderHeadNoteDebrisLWPrefab() = burstSliderHeadNoteDebrisLWPrefab;
        self->dyn__burstSliderElementNoteLWPrefab() = burstSliderElementNoteLWPrefab;
    }
}

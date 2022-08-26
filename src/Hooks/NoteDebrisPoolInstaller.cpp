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
    auto normalNoteDebrisHDPrefab = self->normalNoteDebrisHDPrefab;
    auto normalNoteDebrisLWPrefab = self->normalNoteDebrisLWPrefab;
    auto burstSliderHeadNoteDebrisHDPrefab = self->burstSliderHeadNoteDebrisHDPrefab;
    auto burstSliderHeadNoteDebrisLWPrefab = self->burstSliderHeadNoteDebrisLWPrefab;
    auto burstSliderElementNoteHDPrefab = self->burstSliderElementNoteHDPrefab;
    auto burstSliderElementNoteLWPrefab = self->burstSliderElementNoteLWPrefab;

    bool hd = self->noteDebrisHDConditionVariable->get_value();
    auto container = self->container;
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
        self->normalNoteDebrisHDPrefab = normalNoteDebrisHDPrefab;
        self->burstSliderHeadNoteDebrisHDPrefab = burstSliderHeadNoteDebrisHDPrefab;
        self->burstSliderElementNoteHDPrefab = burstSliderElementNoteHDPrefab;
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
        self->normalNoteDebrisLWPrefab = normalNoteDebrisLWPrefab;
        self->burstSliderHeadNoteDebrisLWPrefab = burstSliderHeadNoteDebrisLWPrefab;
        self->burstSliderElementNoteLWPrefab = burstSliderElementNoteLWPrefab;
    }
}

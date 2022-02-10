#include "Redecoration.hpp"
#include "RedecorationMacros.hpp"
#include "hooks.hpp"
#include "logging.hpp"

#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/SaberModelContainer.hpp"
#include "GlobalNamespace/SaberModelController.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/Transform.hpp"

MAKE_AUTO_HOOK_ORIG_MATCH(SaberModelContainer_Start, &GlobalNamespace::SaberModelContainer::Start, void, GlobalNamespace::SaberModelContainer* self)
{
    auto saberModelControllerPrefab = self->dyn__saberModelControllerPrefab();
    MAKE_CLONE_AND_PARENT(saberModelControllerPrefab);

    static auto self_type = il2cpp_utils::GetSystemType(il2cpp_utils::ExtractType(self->klass));
    auto container = self->dyn__container();

    REDECORATE(saberModelControllerPrefab);

    SaberModelContainer_Start(self);

    self->dyn__saberModelControllerPrefab() = saberModelControllerPrefab;
}
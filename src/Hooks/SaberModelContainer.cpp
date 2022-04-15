#include "SaberModelFactoryRegister_Internal.hpp"
#include "hooks.hpp"
#include "logging.hpp"

#include "SaberModelController.hpp"

#include "GlobalNamespace/ColorManager.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/SaberModelContainer.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/Transform.hpp"

#include "Zenject/DiContainer.hpp"

MAKE_AUTO_HOOK_ORIG_MATCH(SaberModelContainer_Start, &GlobalNamespace::SaberModelContainer::Start, void, GlobalNamespace::SaberModelContainer* self)
{
    auto registrations = Qosmetics::Core::SaberModelFactoryRegister::GetRegistrations();
    Qosmetics::Core::SaberModelController* customSaber = nullptr;
    auto saber = self->dyn__saber();
    for (auto reg : registrations)
    {
        customSaber = reg->MakeSaber(saber->get_saberType());
        if (customSaber)
            break;
    }

    if (!customSaber)
    {
        SaberModelContainer_Start(self);
        return;
    }

    auto colorManager = self->dyn__container()->TryResolve<GlobalNamespace::ColorManager*>();
    customSaber->saber = saber;
    customSaber->colorManager = colorManager;

    auto* initMethod = il2cpp_functions::class_get_method_from_name(il2cpp_utils::ExtractClass(customSaber), "Init", 2);
    if (initMethod)
        il2cpp_utils::RunMethod(customSaber, initMethod, self->get_transform(), saber);
    else
        ERROR("Could not Find Init method on type {}::{}(UnityEngine::Transform* parent, GlobalNamespace::Saber* saber), make sure it's defined!", customSaber->klass->namespaze, customSaber->klass->name);
}
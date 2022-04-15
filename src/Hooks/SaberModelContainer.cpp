#include "Redecoration.hpp"
#include "RedecorationMacros.hpp"
#include "SaberModelFactoryRegister_Internal.hpp"
#include "hooks.hpp"
#include "logging.hpp"

#include "SaberModelController.hpp"

#include "GlobalNamespace/ColorManager.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/SaberModelContainer.hpp"
#include "GlobalNamespace/SaberModelController.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/Transform.hpp"

#include "Zenject/DiContainer.hpp"

MAKE_AUTO_HOOK_ORIG_MATCH(SaberModelContainer_Start, &GlobalNamespace::SaberModelContainer::Start, void, GlobalNamespace::SaberModelContainer* self)
{
    // implement original code more or less
    auto saberModelControllerPrefab = self->dyn__saberModelControllerPrefab();

    auto container = self->dyn__container();
    auto saber = self->dyn__saber();

    auto saberModelControllerGO = self->dyn__container()->InstantiatePrefab(reinterpret_cast<UnityEngine::Object*>(saberModelControllerPrefab));
    auto saberModelController = saberModelControllerGO->GetComponent<GlobalNamespace::SaberModelController*>();
    saberModelController->Init(self->get_transform(), saber);

    auto colorManager = container->TryResolve<GlobalNamespace::ColorManager*>();
    // our custom code to change game behaviour
    auto registrations = Qosmetics::Core::SaberModelFactoryRegister::GetRegistrations();
    for (auto reg : registrations)
    {
        auto customController = reinterpret_cast<Qosmetics::Core::SaberModelController*>(saberModelControllerGO->AddComponent(reg->get_saberModelControllertype()));
        if (!customController)
            ERROR("Failed to Add Custom controller to saber model controller gameobject");
        customController->colorManager = colorManager;
        auto* initMethod = il2cpp_functions::class_get_method_from_name(il2cpp_utils::ExtractClass(customController), "Init", 1);
        if (initMethod)
            il2cpp_utils::RunMethod(customController, initMethod, saber);
        else
            ERROR("Could not Find Init method on type {}::{}(GlobalNamespace::Saber* saber), make sure it's defined!", customController->klass->namespaze, customController->klass->name);
    }
}
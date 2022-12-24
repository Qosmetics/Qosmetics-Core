#include "Installers/MenuInstaller.hpp"
#include "logging.hpp"

#include "UI/CreditViewController.hpp"
#include "UI/GameplaySetupView.hpp"
#include "UI/ProfileSwitcherViewController.hpp"
#include "UI/QosmeticsFlowCoordinator.hpp"
#include "UI/QosmeticsViewController.hpp"

#include "Zenject/ConcreteIdBinderGeneric_1.hpp"
#include "Zenject/DiContainer.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"

#include "lapiz/shared/utilities/ZenjectExtensions.hpp"

DEFINE_TYPE(Qosmetics::Core, MenuInstaller);

void Qosmetics::Core::MenuInstaller::InstallBindings()
{
    auto container = get_Container();

    Lapiz::Zenject::ZenjectExtensions::FromNewComponentOnNewGameObject(container->BindInterfacesAndSelfTo<Qosmetics::Core::QosmeticsFlowCoordinator*>())->AsSingle()->NonLazy();

    Lapiz::Zenject::ZenjectExtensions::FromNewComponentAsViewController(container->Bind<Qosmetics::Core::ProfileSwitcherViewController*>())->AsSingle();
    Lapiz::Zenject::ZenjectExtensions::FromNewComponentAsViewController(container->Bind<Qosmetics::Core::QosmeticsViewController*>())->AsSingle();
    Lapiz::Zenject::ZenjectExtensions::FromNewComponentAsViewController(container->Bind<Qosmetics::Core::CreditViewController*>())->AsSingle();

    container->BindInterfacesAndSelfTo<GameplaySetupView*>()->AsSingle();
}
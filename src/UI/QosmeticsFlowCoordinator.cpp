#include "UI/QosmeticsFlowCoordinator.hpp"
#include "UI/CreditViewController.hpp"
#include "UI/ProfileSwitcherViewController.hpp"
#include "UI/QosmeticsViewController.hpp"
#include "Utils/DateUtils.hpp"
#include "Utils/RainbowUtils.hpp"
#include "Utils/UIUtils.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "static-defines.hpp"

#include "HMUI/TitleViewController.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

DEFINE_TYPE(Qosmetics::Core, QosmeticsFlowCoordinator);

using namespace QuestUI::BeatSaberUI;

namespace Qosmetics::Core
{
    void QosmeticsFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (firstActivation)
        {
            profileSwitcherViewController = CreateViewController<ProfileSwitcherViewController*>();
            qosmeticsViewController = CreateViewController<QosmeticsViewController*>();
            reinterpret_cast<QosmeticsViewController*>(qosmeticsViewController)->qosmeticsFlowCoordinator = this;
            creditViewController = CreateViewController<CreditViewController*>();

            ProvideInitialViewControllers(qosmeticsViewController, profileSwitcherViewController, creditViewController, nullptr, nullptr);

            set_showBackButton(true);

            time_t rawtime = time(nullptr);
            tm localTime = *localtime(&rawtime);
            SetTitle(DateUtils::isMonth(6) ? RainbowUtils::gayify("Qosmetics") : "Qosmetics", HMUI::ViewController::AnimationType::In);
        }

        creditViewController->get_gameObject()->SetActive(true);
        HMUI::TitleViewController* titleView = Object::FindObjectOfType<HMUI::TitleViewController*>();
        UIUtils::SetTitleColor(titleView, qosmetics_purple);
    }

    void QosmeticsFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController)
    {
        creditViewController->get_gameObject()->SetActive(false);
        this->parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
        HMUI::TitleViewController* titleView = Object::FindObjectOfType<HMUI::TitleViewController*>();
        UIUtils::SetTitleColor(titleView, beatsaber_light_blue, true);
    }
}
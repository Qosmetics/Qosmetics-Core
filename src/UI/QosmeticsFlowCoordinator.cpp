#include "UI/QosmeticsFlowCoordinator.hpp"
#include "Data/Creators.hpp"
#include "UI/CreditViewController.hpp"
#include "UI/ProfileSwitcherViewController.hpp"
#include "UI/QosmeticsViewController.hpp"
#include "Utils/DateUtils.hpp"
#include "Utils/RainbowUtils.hpp"
#include "Utils/UIUtils.hpp"
#include "logging.hpp"
#include "static-defines.hpp"

#include "HMUI/TitleViewController.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "Polyglot/LocalizedTextMeshProUGUI.hpp"
#include "UnityEngine/Events/UnityAction.hpp"

#include "custom-types/shared/delegate.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

#include "assets.hpp"
DEFINE_TYPE(Qosmetics::Core, QosmeticsFlowCoordinator);

using namespace QuestUI::BeatSaberUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace Qosmetics::Core
{
    void QosmeticsFlowCoordinator::Inject(Qosmetics::Core::CreditViewController* creditViewController, Qosmetics::Core::ProfileSwitcherViewController* profileSwitcherViewController, Qosmetics::Core::QosmeticsViewController* qosmeticsViewController, GlobalNamespace::MainFlowCoordinator* mainFlowCoordinator)
    {
        this->creditViewController = creditViewController;
        this->profileSwitcherViewController = profileSwitcherViewController;
        this->qosmeticsViewController = qosmeticsViewController;
        this->mainFlowCoordinator = mainFlowCoordinator;
        qosmeticsViewController->qosmeticsFlowCoordinator = this;
    }

    void QosmeticsFlowCoordinator::Initialize()
    {
        Qosmetics::Core::Creators::Download();

        auto optionsViewController = mainFlowCoordinator->optionsViewController;

        bool questUIExists = QuestUI::GetModsCount() > 0;
        Button* baseButton = optionsViewController->settingsButton;
        Button* button = Object::Instantiate(baseButton);
        button->set_name("Qosmetics Settings");

        UnityEngine::Transform* wrapper = optionsViewController->get_transform()->Find("Wrapper");
        button->get_transform()->SetParent(wrapper, false);

        // TODO: update check to run with BSML stuff instead
        // also all round just actually use bsml for UI
        if (questUIExists)
        {
            HorizontalLayoutGroup* layout = CreateHorizontalLayoutGroup(optionsViewController->get_transform());

            Transform* layoutTransform = layout->get_transform();
            optionsViewController->editAvatarButton->get_transform()->SetParent(layoutTransform);
            optionsViewController->playerOptionsButton->get_transform()->SetParent(layoutTransform);
            optionsViewController->settingsButton->get_transform()->SetParent(layoutTransform);

            layoutTransform->SetAsFirstSibling();
            layout->set_spacing(-64.0f);
            layout->get_gameObject()->GetComponent<UnityEngine::RectTransform*>()->set_anchoredPosition(UnityEngine::Vector2(0.0f, -7.5f));

            HorizontalLayoutGroup* oldLayout = wrapper->get_gameObject()->GetComponent<HorizontalLayoutGroup*>();
            oldLayout->get_gameObject()->GetComponent<RectTransform*>()->set_anchoredPosition(UnityEngine::Vector2(0.0f, 0.0f));
            button->get_transform()->SetAsLastSibling();
        }
        else
            button->get_transform()->SetAsFirstSibling();

        auto delegate = custom_types::MakeDelegate<UnityEngine::Events::UnityAction*>(
            std::function<void()>([this]()
                                  { PresentSelf(); }));
        button->get_onClick()->AddListener(delegate);

        SetButtonSprites(button, ArrayToSprite(IncludedAssets::MenuIcon_png), ArrayToSprite(IncludedAssets::MenuIconSelected_png));

        UnityEngine::Object::Destroy(button->GetComponentInChildren<Polyglot::LocalizedTextMeshProUGUI*>());

        button->GetComponentInChildren<TMPro::TextMeshProUGUI*>()->SetText("Qosmetics Settings");
    }

    void QosmeticsFlowCoordinator::PresentSelf()
    {
        if (!mainFlowCoordinator || !mainFlowCoordinator->m_CachedPtr.m_value)
            return;
        mainFlowCoordinator->YoungestChildFlowCoordinatorOrSelf()->PresentFlowCoordinator(this, nullptr, HMUI::ViewController::AnimationDirection::Horizontal, false, false);
    }

    void QosmeticsFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (firstActivation)
        {
            ProvideInitialViewControllers(qosmeticsViewController, profileSwitcherViewController, creditViewController, nullptr, nullptr);

            set_showBackButton(true);

            time_t rawtime = time(nullptr);
            tm localTime = *localtime(&rawtime);
            SetTitle(GetTitle(), HMUI::ViewController::AnimationType::In);
        }

        creditViewController->get_gameObject()->SetActive(true);
        HMUI::TitleViewController* titleView = Object::FindObjectOfType<HMUI::TitleViewController*>();
        UIUtils::SetTitleColor(titleView, qosmetics_purple);
    }

    StringW QosmeticsFlowCoordinator::GetTitle()
    {
        return DateUtils::isMonth(6) ? RainbowUtils::gayify("Qosmetics") : "Qosmetics";
    }

    void QosmeticsFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController)
    {
        creditViewController->get_gameObject()->SetActive(false);
        this->parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
        HMUI::TitleViewController* titleView = Object::FindObjectOfType<HMUI::TitleViewController*>();
        UIUtils::SetTitleColor(titleView, beatsaber_light_blue, true);
    }
}
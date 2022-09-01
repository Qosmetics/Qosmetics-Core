#include "UI/QosmeticsViewController.hpp"
#include "diglett/shared/Localization.hpp"
#include "diglett/shared/Util.hpp"
#include "logging.hpp"

#include "HMUI/ViewController_AnimationDirection.hpp"
#include "UI/QosmeticsBaseFlowCoordinator.hpp"
#include "questui/shared/BeatSaberUI.hpp"

DEFINE_TYPE(Qosmetics::Core, QosmeticsViewController);

using namespace QuestUI::BeatSaberUI;

namespace Qosmetics::Core
{
    void QosmeticsViewController::Inject(ListWrapper<Qosmetics::Core::QosmeticsBaseFlowCoordinator*> baseFlowCoordinators)
    {
        INFO("Inject");
        // this should get all the QosmeticsBaseFlowCoordinators :)
        flowCoordinators = baseFlowCoordinators->ToArray();
    }

    void QosmeticsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (firstActivation)
        {
            auto horizontal = CreateHorizontalLayoutGroup(get_transform());
            if (!flowCoordinators || flowCoordinators.size() == 0)
            {
                auto text = CreateText(horizontal->get_transform(), Diglett::Localization::get_instance()->get("QosmeticsCore:Misc:ModulesMissing"));
                text->set_alignment(TMPro::TextAlignmentOptions::Center);
            }
            else
            {
                for (auto* reg : flowCoordinators)
                {
                    auto btn = CreateUIButton(horizontal->get_transform(), reg->name, "SettingsButton", {0, 0}, {0, 0}, std::bind(&QosmeticsViewController::PresentFlowCoordinator, this, reg));
                    SetButtonSprites(btn, reg->inActiveSprite, reg->activeSprite);
                }
            }
        }
    }

    void QosmeticsViewController::PresentFlowCoordinator(Qosmetics::Core::QosmeticsBaseFlowCoordinator* flowCoordinator)
    {
        if (!qosmeticsFlowCoordinator || !qosmeticsFlowCoordinator->m_CachedPtr.m_value)
            return;
        if (!flowCoordinator || !flowCoordinator->m_CachedPtr.m_value)
            return;

        DEBUG("Presenting {} on parent {}", fmt::ptr(flowCoordinator), fmt::ptr(qosmeticsFlowCoordinator));
        qosmeticsFlowCoordinator->PresentFlowCoordinator(flowCoordinator, nullptr, HMUI::ViewController::AnimationDirection::Horizontal, false, false);
    }
}
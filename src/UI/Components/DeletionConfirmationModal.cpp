#include "UI/Components/DeletionConfirmationModal.hpp"
#include "UI/Components/QosmeticObjectTableCell.hpp"
#include "diglett/shared/Localization.hpp"
#include "diglett/shared/Util.hpp"

#include "questui/shared/BeatSaberUI.hpp"

#include "System/Action.hpp"
#include "TMPro/TextAlignmentOptions.hpp"
#include "UnityEngine/RectOffset.hpp"

#include "custom-types/shared/delegate.hpp"

DEFINE_TYPE(Qosmetics::Core, DeletionConfirmationModal);

using namespace QuestUI::BeatSaberUI;
using namespace UnityEngine;

#define MakeDelegate(DelegateType, varName) (custom_types::MakeDelegate<DelegateType>(varName))

namespace Qosmetics::Core
{
    DeletionConfirmationModal* DeletionConfirmationModal::Create(UnityEngine::Transform* parent)
    {
        auto baseModal = CreateModal(parent, Vector2(50, 30), nullptr, true);
        auto go = baseModal->get_gameObject();
        auto presentPanelAnimations = baseModal->presentPanelAnimations;
        auto dismissPanelAnimation = baseModal->dismissPanelAnimation;
        auto container = baseModal->container;

        Object::DestroyImmediate(baseModal);
        auto modal = go->AddComponent<DeletionConfirmationModal*>();
        modal->presentPanelAnimations = presentPanelAnimations;
        modal->dismissPanelAnimation = dismissPanelAnimation;
        modal->container = container;

        std::function<void()> onBlockerClicked = std::bind(&DeletionConfirmationModal::Dismiss, modal);
        modal->add_blockerClickedEvent(MakeDelegate(System::Action*, onBlockerClicked));
        modal->Setup();
        return modal;
    }

    void DeletionConfirmationModal::Setup()
    {
        auto localization = Diglett::Localization::get_instance();
        auto vertical = CreateVerticalLayoutGroup(get_transform());
        vertical->set_padding(RectOffset::New_ctor(2, 2, 2, 2));
        auto headerText = CreateText(vertical->get_transform(), localization->get("QosmeticsCore:DeletionConfirmation:AreYouSure"));
        headerText->set_alignment(TMPro::TextAlignmentOptions::Center);
        objectName = CreateText(vertical->get_transform(), "---");
        objectName->set_alignment(TMPro::TextAlignmentOptions::Center);
        auto buttonHorizontal = CreateHorizontalLayoutGroup(vertical->get_transform());
        auto confirmBtn = CreateUIButton(buttonHorizontal->get_transform(), u"<color=#ff0404>" + localization->get("QosmeticsCore:DeletionConfirmation:Confirm") + u"</color>", std::bind(&DeletionConfirmationModal::Confirm, this));
        auto cancelBtn = CreateUIButton(buttonHorizontal->get_transform(), u"<color=#04ff04>" + localization->get("QosmeticsCore:DeletionConfirmation:Cancel") + u"</color>", std::bind(&DeletionConfirmationModal::Dismiss, this));
    }

    void DeletionConfirmationModal::Show(QosmeticObjectTableCell* cellToDelete)
    {
        currentCell = cellToDelete;
        objectName->set_text(currentCell->descriptor.get_name());
        this->HMUI::ModalView::Show(true, true, nullptr);
    }

    void DeletionConfirmationModal::Dismiss()
    {
        Hide(true, nullptr);
    }

    void DeletionConfirmationModal::Confirm()
    {
        currentCell->Delete();
    }
}
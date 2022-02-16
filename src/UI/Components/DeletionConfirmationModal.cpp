#include "UI/Components/DeletionConfirmationModal.hpp"
#include "UI/Components/QosmeticObjectTableCell.hpp"
#include "diglett/shared/Diglett.hpp"
#include "questui/shared/BeatSaberUI.hpp"

#include "System/Action.hpp"
#include "TMPro/TextAlignmentOptions.hpp"
#include "UnityEngine/RectOffset.hpp"

DEFINE_TYPE(Qosmetics::Core, DeletionConfirmationModal);

using namespace QuestUI::BeatSaberUI;
using namespace UnityEngine;

#define MakeDelegate(DelegateType, varName) (il2cpp_utils::MakeDelegate<DelegateType>(classof(DelegateType), varName))

namespace Qosmetics::Core
{
    DeletionConfirmationModal* DeletionConfirmationModal::Create(UnityEngine::Transform* parent)
    {
        auto baseModal = CreateModal(parent, Vector2(50, 30), nullptr, true);
        auto go = baseModal->get_gameObject();
        auto presentPanelAnimations = baseModal->dyn__presentPanelAnimations();
        auto dismissPanelAnimation = baseModal->dyn__dismissPanelAnimation();
        auto container = baseModal->dyn__container();

        Object::DestroyImmediate(baseModal);
        auto modal = go->AddComponent<DeletionConfirmationModal*>();
        modal->dyn__presentPanelAnimations() = presentPanelAnimations;
        modal->dyn__dismissPanelAnimation() = dismissPanelAnimation;
        modal->dyn__container() = container;

        std::function<void()> onBlockerClicked = std::bind(&DeletionConfirmationModal::Dismiss, modal);
        modal->add_blockerClickedEvent(MakeDelegate(System::Action*, onBlockerClicked));
        modal->Setup();
        return modal;
    }

    void DeletionConfirmationModal::Setup()
    {
        auto localization = Localization::GetSelected();
        auto vertical = CreateVerticalLayoutGroup(get_transform());
        vertical->set_padding(RectOffset::New_ctor(2, 2, 2, 2));
        auto headerText = CreateText(vertical->get_transform(), localization->Get("QosmeticsCore:DeletionConfirmation:AreYouSure"));
        headerText->set_alignment(TMPro::TextAlignmentOptions::Center);
        objectName = CreateText(vertical->get_transform(), "---");
        objectName->set_alignment(TMPro::TextAlignmentOptions::Center);
        auto buttonHorizontal = CreateHorizontalLayoutGroup(vertical->get_transform());
        auto confirmBtn = CreateUIButton(buttonHorizontal->get_transform(), u"<color=#ff0404>" + localization->Get("QosmeticsCore:DeletionConfirmation:Confirm") + u"</color>", std::bind(&DeletionConfirmationModal::Confirm, this));
        auto cancelBtn = CreateUIButton(buttonHorizontal->get_transform(), u"<color=#04ff04>" + localization->Get("QosmeticsCore:DeletionConfirmation:Cancel") + u"</color>", std::bind(&DeletionConfirmationModal::Dismiss, this));
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
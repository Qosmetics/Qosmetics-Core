#include "UI/Components/DeletionConfirmationModal.hpp"
#include "UI/Components/QosmeticObjectTableCell.hpp"

#include "assets.hpp"
#include "bsml/shared/BSML.hpp"

#include "custom-types/shared/delegate.hpp"

DEFINE_TYPE(Qosmetics::Core, DeletionConfirmationModal);

using namespace UnityEngine;

namespace Qosmetics::Core
{
    DeletionConfirmationModal* DeletionConfirmationModal::Create(UnityEngine::Transform* parent)
    {
        auto modal = parent->get_gameObject()->AddComponent<DeletionConfirmationModal*>();
        BSML::parse_and_construct(Assets::DeletionConfirmationModal_bsml, parent, modal);
        return modal;
    }

    void DeletionConfirmationModal::Show(QosmeticObjectTableCell* cellToDelete)
    {
        currentCell = cellToDelete;
        objectName->set_text(currentCell->descriptor.get_name());
        modal->Show();
    }

    void DeletionConfirmationModal::Dismiss()
    {
        modal->Hide();
    }

    void DeletionConfirmationModal::Confirm()
    {
        modal->Hide();
        currentCell->Delete();
        currentCell = nullptr;
    }
}

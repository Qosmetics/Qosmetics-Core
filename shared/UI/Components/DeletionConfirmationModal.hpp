#pragma once

#include "HMUI/ModalView.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "bsml/shared/BSML/Components/ModalView.hpp"
#include "custom-types/shared/macros.hpp"

namespace Qosmetics::Core
{
    class QosmeticObjectTableCell;
}

DECLARE_CLASS_CODEGEN(Qosmetics::Core, DeletionConfirmationModal, UnityEngine::MonoBehaviour,
                      DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, objectName);
                      DECLARE_INSTANCE_FIELD(BSML::ModalView*, modal);
                      DECLARE_INSTANCE_METHOD(void, Dismiss);
                      DECLARE_INSTANCE_METHOD(void, Confirm);

                      public
                      : static DeletionConfirmationModal * Create(UnityEngine::Transform * parent);
                      void Show(QosmeticObjectTableCell* cellToDelete);

                      QosmeticObjectTableCell * currentCell;

)
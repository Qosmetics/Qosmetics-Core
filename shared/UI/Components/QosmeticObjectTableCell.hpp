#pragma once

#include "../../Data/Descriptor.hpp"
#include "DeletionConfirmationModal.hpp"
#include "HMUI/HoverHint.hpp"
#include "HMUI/ImageView.hpp"
#include "HMUI/TableCell.hpp"
#include "QosmeticObjectTableData.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/EventSystems/BaseEventData.hpp"
#include "UnityEngine/EventSystems/PointerEventData.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "custom-types/shared/macros.hpp"
#include <functional>

#include "bsml/shared/BSML/Components/Backgroundable.hpp"
#include "bsml/shared/BSML/Components/ClickableImage.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Core, QosmeticObjectTableCell, HMUI::TableCell,
        DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, _name);
        DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, _sub);
        DECLARE_INSTANCE_FIELD(HMUI::HoverHint*, _hover);
        DECLARE_INSTANCE_FIELD(HMUI::ImageView*, _image);
        DECLARE_INSTANCE_FIELD(BSML::Backgroundable*, _backgroundImage);
        DECLARE_INSTANCE_FIELD(BSML::ClickableImage*, _deleteBtn);

        DECLARE_INSTANCE_FIELD(DeletionConfirmationModal*, _deletionConfirmationModal);
        DECLARE_INSTANCE_FIELD(QosmeticObjectTableData*, _tableData);

        DECLARE_INSTANCE_METHOD(void, PostParse);
        DECLARE_INSTANCE_METHOD(void, Select);
        DECLARE_INSTANCE_METHOD(void, Delete);
        DECLARE_INSTANCE_METHOD(void, AttemptDelete);
        DECLARE_OVERRIDE_METHOD_MATCH(void, HighlightDidChange, &HMUI::SelectableCell::HighlightDidChange, HMUI::SelectableCell::TransitionType transitionType);

    public:
        static Qosmetics::Core::QosmeticObjectTableCell* CreateNewCell();

        void SetDescriptor(Descriptor const& descriptor);

        void set_name(std::string_view name);
        __declspec(property(put=set_name)) std::string_view name;

        void set_sub(std::string_view sub);
        __declspec(property(put=set_sub)) std::string_view sub;

        void set_hover(std::string_view hover);
        __declspec(property(put=set_hover)) std::string_view hover;

        void set_sprite(UnityEngine::Sprite* preview);
        __declspec(property(put=set_sprite)) UnityEngine::Sprite* sprite;

        void LoadPreviewImage();

        std::function<void(QosmeticObjectTableCell*)> onSelect;
        std::function<void(QosmeticObjectTableCell*)> onDelete;
        Descriptor descriptor;

)

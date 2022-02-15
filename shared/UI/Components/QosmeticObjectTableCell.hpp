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
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include <functional>

#ifndef DECLARE_OVERRIDE_METHOD_MATCH
#define DECLARE_OVERRIDE_METHOD_MATCH(retval, method, mptr, ...) \
    DECLARE_OVERRIDE_METHOD(retval, method, il2cpp_utils::il2cpp_type_check::MetadataGetter<mptr>::get(), __VA_ARGS__)
#endif

DECLARE_CLASS_CODEGEN(Qosmetics::Core, QosmeticObjectTableCell, HMUI::TableCell,

                      DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, name);
                      DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, sub);
                      DECLARE_INSTANCE_FIELD(HMUI::HoverHint*, hover);
                      DECLARE_INSTANCE_FIELD(HMUI::ImageView*, image);
                      DECLARE_INSTANCE_FIELD(HMUI::ImageView*, backgroundImage);

                      DECLARE_INSTANCE_FIELD(DeletionConfirmationModal*, deletionConfirmationModal);
                      DECLARE_INSTANCE_FIELD(QosmeticObjectTableData*, tableData);

                      DECLARE_OVERRIDE_METHOD_MATCH(void, HighlightDidChange, &HMUI::SelectableCell::HighlightDidChange, HMUI::SelectableCell::TransitionType transitionType);

                      public
                      :

                      static Qosmetics::Core::QosmeticObjectTableCell * CreateNewCell();
                      void Setup();

                      void Select();
                      void Delete();
                      void AttemptDelete();

                      void SetDescriptor(Descriptor descriptor);
                      void set_name(std::string_view name);
                      void set_sub(std::string_view sub);
                      void set_hover(std::string_view hover);
                      void set_sprite(UnityEngine::Sprite* preview);

                      void LoadPreviewImage();
                      custom_types::Helpers::Coroutine DownloadPreviewImage();

                      std::function<void(QosmeticObjectTableCell*)> onSelect;
                      std::function<void(QosmeticObjectTableCell*)> onDelete;
                      Descriptor descriptor;

)
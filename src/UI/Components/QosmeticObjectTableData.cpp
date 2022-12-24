#include "UI/Components/QosmeticObjectTableData.hpp"
#include "UI/Components/QosmeticObjectTableCell.hpp"
#include "assets.hpp"

#include "System/Action_2.hpp"
#include "bsml/shared/Helpers/utilities.hpp"

#include "custom-types/shared/delegate.hpp"

DEFINE_TYPE(Qosmetics::Core, QosmeticObjectTableData);

namespace Qosmetics::Core
{
    void QosmeticObjectTableData::ctor()
    {
        INVOKE_CTOR();
        reuseIdentifier = StringW("QosmeticObjectCellList");
        cellSize = 12.0f;

        previewToSpriteDict = StringToSpriteDict::New_ctor();
    }

    void QosmeticObjectTableData::Start()
    {
        using DelegateType = System::Action_2<HMUI::TableView*, int>;
        std::function<void(HMUI::TableView*, int)> fun = std::bind(&QosmeticObjectTableData::DidSelectCellWithIdx, this, std::placeholders::_1, std::placeholders::_2);
        auto delegate = custom_types::MakeDelegate<DelegateType*>(fun);
        tableView->add_didSelectCellWithIdxEvent(delegate);
    }

    void QosmeticObjectTableData::DidSelectCellWithIdx(HMUI::TableView* tableView, int idx)
    {
        if (onSelect)
        {
            auto& desc = *std::next(objectDescriptors.begin(), idx);
            ListWrapper<QosmeticObjectTableCell*> visibleCells(reinterpret_cast<List<QosmeticObjectTableCell*>*>(tableView->visibleCells));

            auto cell = std::find_if(visibleCells.begin(), visibleCells.end(), [desc](auto x)
                                     { return desc.get_filePath() == x->descriptor.get_filePath(); });
            if (cell != visibleCells.end())
                (*cell)->Select();
        }
    }

    float QosmeticObjectTableData::CellSize()
    {
        return cellSize;
    }

    int QosmeticObjectTableData::NumberOfCells()
    {
        return objectDescriptors.size();
    }

    HMUI::TableCell* QosmeticObjectTableData::CellForIdx(HMUI::TableView* tableView, int idx)
    {
        auto tableCell = reinterpret_cast<QosmeticObjectTableCell*>(tableView->DequeueReusableCellForIdentifier(reuseIdentifier));

        if (!tableCell)
        {
            tableCell = QosmeticObjectTableCell::CreateNewCell();
        }

        tableCell->tableData = this;
        tableCell->deletionConfirmationModal = deletionConfirmationModal;
        tableCell->set_reuseIdentifier(reuseIdentifier);
        tableCell->SetDescriptor(*std::next(objectDescriptors.begin(), idx));
        if (onSelect)
            tableCell->onSelect = onSelect;
        if (onDelete)
            tableCell->onDelete = onDelete;

        return tableCell;
    }

    UnityEngine::Sprite* QosmeticObjectTableData::DefaultSprite()
    {
        if (defaultSprite && defaultSprite->m_CachedPtr.m_value)
            return defaultSprite;

        defaultSprite = BSML::Utilities::LoadSpriteRaw(IncludedAssets::PlaceHolderImage_png);
        return defaultSprite;
    }

    UnityEngine::Sprite* QosmeticObjectTableData::GetCachedSprite(StringW key)
    {
        return previewToSpriteDict->ContainsKey(key) ? previewToSpriteDict->get_Item(key) : nullptr;
    }

    void QosmeticObjectTableData::AddCachedSprite(StringW key, UnityEngine::Sprite* sprite)
    {
        if (!previewToSpriteDict->ContainsKey(key))
            previewToSpriteDict->Add(key, sprite);
    }

}

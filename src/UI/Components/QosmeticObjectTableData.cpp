#include "UI/Components/QosmeticObjectTableData.hpp"
#include "UI/Components/QosmeticObjectTableCell.hpp"
#include "assets.hpp"
#include "questui/shared/BeatSaberUI.hpp"

DEFINE_TYPE(Qosmetics::Core, QosmeticObjectTableData);

namespace Qosmetics::Core
{
    void QosmeticObjectTableData::ctor()
    {
        INVOKE_CTOR();
        reuseIdentifier = il2cpp_utils::newcsstr("QosmeticObjectCellList");
        cellSize = 12.0f;

        previewToSpriteDict = StringToSpriteDict::New_ctor();
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
            tableCell->set_interactable(false);
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
        if (defaultSprite)
            return defaultSprite;

        defaultSprite = QuestUI::BeatSaberUI::VectorToSprite(std::vector<uint8_t>(_binary_PlaceHolderImage_png_start, _binary_PlaceHolderImage_png_end));
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

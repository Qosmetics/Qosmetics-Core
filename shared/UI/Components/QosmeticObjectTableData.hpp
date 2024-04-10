#pragma once

#include "../../Data/Descriptor.hpp"
#include "DeletionConfirmationModal.hpp"
#include "HMUI/TableCell.hpp"
#include "HMUI/TableView.hpp"
#include "System/Collections/Generic/Dictionary_2.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Sprite.hpp"
#include "custom-types/shared/macros.hpp"
#include <functional>
#include <set>

DECLARE_CLASS_CODEGEN_INTERFACES(Qosmetics::Core, QosmeticObjectTableData, UnityEngine::MonoBehaviour, classof(HMUI::TableView::IDataSource*),
                                 DECLARE_INSTANCE_FIELD(HMUI::TableView*, tableView);
                                 DECLARE_INSTANCE_FIELD(Il2CppString*, reuseIdentifier);
                                 DECLARE_INSTANCE_FIELD(float, cellSize);
                                 DECLARE_INSTANCE_FIELD(DeletionConfirmationModal*, deletionConfirmationModal);
                                 using StringToSpriteDict = System::Collections::Generic::Dictionary_2<StringW, UnityEngine::Sprite*>;
                                 DECLARE_INSTANCE_FIELD(StringToSpriteDict*, previewToSpriteDict);
                                 DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, defaultSprite);

                                 DECLARE_CTOR(ctor);

                                 DECLARE_INSTANCE_METHOD(void, Start);
                                 DECLARE_INSTANCE_METHOD(void, DidSelectCellWithIdx, HMUI::TableView* tableView, int idx);
                                 DECLARE_INSTANCE_METHOD(UnityEngine::Sprite*, DefaultSprite);
                                 DECLARE_INSTANCE_METHOD(UnityEngine::Sprite*, GetCachedSprite, StringW key);
                                 DECLARE_INSTANCE_METHOD(void, AddCachedSprite, StringW key, UnityEngine::Sprite* sprite);

                                 DECLARE_OVERRIDE_METHOD_MATCH(HMUI::TableCell*, CellForIdx, &HMUI::TableView::IDataSource::CellForIdx, HMUI::TableView* tableView, int idx);
                                 DECLARE_OVERRIDE_METHOD_MATCH(float, CellSize, &HMUI::TableView::IDataSource::CellSize);
                                 DECLARE_OVERRIDE_METHOD_MATCH(int, NumberOfCells, &HMUI::TableView::IDataSource::NumberOfCells);

                                 public
                                 :

                                 std::function<void(HMUI::TableCell*)> onSelect = nullptr;
                                 std::function<void(HMUI::TableCell*)> onDelete = nullptr;
                                 std::set<Descriptor, DescriptorComparator> objectDescriptors = {};

)

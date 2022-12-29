#pragma once

#include "bsml/shared/BSML/Components/CustomListTableData.hpp"
#include "bsml/shared/BSML/Components/ModalView.hpp"
#include "bsml/shared/BSML/Components/Settings/StringSetting.hpp"
#include "custom-types/shared/macros.hpp"

#include "HMUI/ViewController.hpp"
#include "custom-types/shared/coroutine.hpp"
#include <string>
#include <vector>

DECLARE_CLASS_CODEGEN(Qosmetics::Core, ProfileSwitcherViewController, HMUI::ViewController,
                      DECLARE_INSTANCE_FIELD(List<BSML::CustomCellInfo*>*, _profiles);
                      DECLARE_INSTANCE_METHOD(ListWrapper<BSML::CustomCellInfo*>, get_profiles);
                      DECLARE_INSTANCE_METHOD(StringW, get_gaydient);
                      DECLARE_INSTANCE_METHOD(bool, get_gay);

                      DECLARE_INSTANCE_METHOD(BSML::CustomCellInfo*, GetSelectedCell);
                      DECLARE_INSTANCE_METHOD(void, ShowDeleteModal);
                      DECLARE_INSTANCE_METHOD(void, ConfirmDelete);
                      DECLARE_INSTANCE_METHOD(void, PostParse);
                      DECLARE_INSTANCE_METHOD(void, ConfirmAddUser);
                      DECLARE_INSTANCE_FIELD(BSML::CustomListTableData*, userList);
                      DECLARE_INSTANCE_FIELD(BSML::StringSetting*, textField);
                      DECLARE_INSTANCE_FIELD(BSML::ModalView*, deleteModal);
                      DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, deleteProfileName);

                      DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::ViewController::DidActivate>::get(), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
                      DECLARE_INSTANCE_METHOD(void, SelectUser, HMUI::TableView* _, int idx);

                      DECLARE_CTOR(ctor);
                      private
                      :

                      void AddUser(std::string_view user);
                      void RefreshUsers(bool alsoRefreshList = true);

)
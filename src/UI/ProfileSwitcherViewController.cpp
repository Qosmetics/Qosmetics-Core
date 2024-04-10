#include "UI/ProfileSwitcherViewController.hpp"
#include "ConfigRegister_Internal.hpp"
#include "Utils/DateUtils.hpp"
#include "Utils/FileUtils.hpp"
#include "Utils/RainbowUtils.hpp"
#include "Utils/UIUtils.hpp"
#include "assets.hpp"
#include "logging.hpp"

#include "static-defines.hpp"

#include "System/Collections/Generic/HashSet_1.hpp"

#include "UnityEngine/UI/LayoutElement.hpp"

#include "bsml/shared/BSML.hpp"
DEFINE_TYPE(Qosmetics::Core, ProfileSwitcherViewController);

using namespace UnityEngine;

namespace Qosmetics::Core
{
    void ProfileSwitcherViewController::ctor()
    {
        _profiles = ListW<BSML::CustomCellInfo*>::New();
        RefreshUsers(false);
    }

    ListW<BSML::CustomCellInfo*> ProfileSwitcherViewController::get_profiles() { return _profiles; }

    bool ProfileSwitcherViewController::get_gay()
    {
        return DateUtils::isMonth(6);
    }

    StringW ProfileSwitcherViewController::get_gaydient()
    {
        return RainbowUtils::randomGradient();
    }

    void ProfileSwitcherViewController::PostParse()
    {
        RefreshUsers();
    }

    void ProfileSwitcherViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (!firstActivation)
            return;
        BSML::parse_and_construct(Assets::Views::ProfileSwitcherView_bsml, get_transform(), this);
    }

    void ProfileSwitcherViewController::ConfirmAddUser()
    {
        if (textField && textField->m_CachedPtr && textField->get_text())
        {
            AddUser(static_cast<std::string>(textField->get_text()));
            textField->set_text("");
        }
    }

    void ProfileSwitcherViewController::AddUser(std::string_view user)
    {
        DEBUG("Trying to add user {}", user);
        std::vector<std::string> profiles = {};
        FileUtils::GetFilesInFolderPath("json", userconfig_path, profiles);
        auto userItr = std::find_if(profiles.begin(), profiles.end(), [&](auto& rhs)
                                    { return user == FileUtils::RemoveExtension(rhs); });

        // if user didn't exist yet
        if (userItr == profiles.end())
        {
            Config::config.lastUsedConfig = std::string(user);
            Config::SaveSpecificConfig(user);
            RefreshUsers();
        }
    }

    void ProfileSwitcherViewController::RefreshUsers(bool alsoRefreshList)
    {
        std::vector<std::string> profiles;
        FileUtils::GetFilesInFolderPath("json", userconfig_path, profiles);
        auto profilesList = get_profiles();
        profilesList->Clear();
        profilesList->EnsureCapacity(profiles.size());

        int counter = 0;
        int userIdx = 0;
        for (auto& profile : profiles)
        {
            auto profileNoExt = FileUtils::RemoveExtension(profile);
            if (profileNoExt == Config::config.lastUsedConfig && userIdx == 0)
                userIdx = counter;
            profilesList->Add(BSML::CustomCellInfo::construct(profileNoExt));
            counter++;
        }

        if (alsoRefreshList)
        {
            userList->tableView->ReloadData();
            userList->tableView->RefreshCells(true, true);
            userList->tableView->ScrollToCellWithIdx(userIdx >= 0 ? userIdx : 0, HMUI::TableView::ScrollPositionType::Beginning, false);
            userList->tableView->SelectCellWithIdx(userIdx, false);
        }
    }

    void ProfileSwitcherViewController::SelectUser(HMUI::TableView* _, int idx)
    {
        auto user = get_profiles()[idx]->text;

        // if different user
        if (user != Config::config.lastUsedConfig)
        {
            //
            Config::config.lastUsedConfig = static_cast<std::string>(user);
            Config::LoadSpecificConfig(Config::config.lastUsedConfig);
            Config::SaveConfig();
            Config::OnProfileSwitched();
        }
    }

    BSML::CustomCellInfo* ProfileSwitcherViewController::GetSelectedCell()
    {
        auto profilesList = get_profiles();
        auto enumerator = userList->tableView->_selectedCellIdxs->GetEnumerator();
        if (!enumerator.MoveNext())
            return nullptr;
        int idx = enumerator.get_Current();
        enumerator.Dispose();
        if (idx < 0 || idx >= profilesList.size())
        {
            ERROR("Index {} is out of range for profiles", idx);
            return nullptr;
        }
        return profilesList[idx];
    }

    void ProfileSwitcherViewController::ShowDeleteModal()
    {
        deleteModal->Show();
        auto selectedCell = GetSelectedCell();
        if (!selectedCell)
        {
            ERROR("No Cell selected, can't show delete modal!");
            return;
        }
        if (selectedCell->text == "Default")
        {
            ERROR("can't allow deleting Default profile!");
            return;
        }
        deleteProfileName->set_text(selectedCell->text);
    }

    void ProfileSwitcherViewController::ConfirmDelete()
    {
        deleteModal->Hide();
        auto toRemove = GetSelectedCell();
        if (!toRemove)
            return;

        // delete file
        auto path = fmt::format("{}/{}.json", userconfig_path, toRemove->text);
        if (!fileexists(path))
        {
            ERROR("Profile at path '{}' Did not exist!", path);
            return;
        }
        else
            deletefile(path);

        // refresh list
        RefreshUsers();
    }
}

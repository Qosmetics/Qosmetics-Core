#include "UI/ProfileSwitcherViewController.hpp"
#include "ConfigRegister_Internal.hpp"
#include "Utils/FileUtils.hpp"
#include "Utils/UIUtils.hpp"
#include "diglett/shared/Localization.hpp"
#include "diglett/shared/Util.hpp"
#include "logging.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/List/QuestUITableView.hpp"
#include "static-defines.hpp"

#include "HMUI/TableView_ScrollPositionType.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"

DEFINE_TYPE(Qosmetics::Core, ProfileSwitcherViewController);

using namespace UnityEngine;
using namespace QuestUI;
using namespace QuestUI::BeatSaberUI;

namespace Qosmetics::Core
{
    void ProfileSwitcherViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (firstActivation)
        {
            auto localization = Diglett::Localization::get_instance();
            UIUtils::AddHeader(get_transform(), localization->get("QosmeticsCore:Settings:Profile"), qosmetics_purple);
            auto vertical = CreateVerticalLayoutGroup(get_transform());

            CreateText(vertical->get_transform(), localization->get("QosmeticsCore:Settings:ProfileMessage"));

            auto addUserHorizontal = CreateHorizontalLayoutGroup(vertical);
            textField = CreateStringSetting(addUserHorizontal->get_transform(), localization->get("QosmeticsCore:Settings:ProfileName"), "",
                                            [&](auto v)
                                            {
                                                if (static_cast<std::u16string_view>(v).size() > 15)
                                                {
                                                    textField->set_text(static_cast<std::u16string_view>(v).substr(0, 15));
                                                }
                                            });
            auto layout = textField->GetComponent<UnityEngine::UI::LayoutElement*>();
            layout->set_preferredWidth(60.0f);
            auto confirm = CreateUIButton(addUserHorizontal->get_transform(), localization->get("QosmeticsCore:Settings:AddProfile"), std::bind(&ProfileSwitcherViewController::ConfirmAddUser, this));
            userList = CreateScrollableList(vertical->get_transform(), {60.0f, 58.5f}, std::bind(&ProfileSwitcherViewController::SelectUser, this, std::placeholders::_1));
            userList->set_listStyle(CustomListTableData::ListStyle::Simple);
            userList->cellSize = 8.5f;

            RefreshUsers();
        }
    }

    void ProfileSwitcherViewController::ConfirmAddUser()
    {
        AddUser(static_cast<std::string>(textField->get_text()));
        textField->set_text("");
        textField->UpdatePlaceholder();
    }

    void ProfileSwitcherViewController::AddUser(std::string_view user)
    {
        std::vector<std::string> profiles = {};
        FileUtils::GetFilesInFolderPath("json", userconfig_path, profiles);
        auto userItr = std::find_if(profiles.begin(), profiles.end(), [&](auto& rhs)
                                    { return user == rhs; });

        // if user didn't exist yet
        if (userItr == profiles.end())
        {
            Config::config.lastUsedConfig = std::string(user);
            Config::SaveSpecificConfig(user);
            RefreshUsers();
        }
    }

    void ProfileSwitcherViewController::RefreshUsers()
    {
        std::vector<std::string> profiles = {};
        FileUtils::GetFilesInFolderPath("json", userconfig_path, profiles);
        userList->data.clear();
        int counter = 0;
        int userIdx = 0;
        for (auto& profile : profiles)
        {
            auto profileNoExt = FileUtils::RemoveExtension(profile);
            if (profileNoExt == Config::config.lastUsedConfig && userIdx == 0)
                userIdx = counter;
            userList->data.emplace_back(std::string(profileNoExt));
            counter++;
        }
        userList->tableView->ReloadData();
        userList->tableView->RefreshCells(true, true);
        userList->tableView->ScrollToCellWithIdx(userIdx >= 0 ? userIdx : 0, HMUI::TableView::ScrollPositionType::Beginning, false);

        userList->tableView->SelectCellWithIdx(userIdx, false);
    }

    void ProfileSwitcherViewController::SelectUser(int idx)
    {
        std::vector<std::string> profiles = {};
        FileUtils::GetFilesInFolderPath("json", userconfig_path, profiles);

        std::string_view user = FileUtils::RemoveExtension(profiles[idx]);

        // if different user
        if (user != Config::config.lastUsedConfig)
        {
            //
            Config::config.lastUsedConfig = std::string(user);
            Config::LoadSpecificConfig(Config::config.lastUsedConfig);
            Config::SaveConfig();
            Config::OnProfileSwitched();
        }
    }
}
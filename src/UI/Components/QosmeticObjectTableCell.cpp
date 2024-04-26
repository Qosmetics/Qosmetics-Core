#include "UI/Components/QosmeticObjectTableCell.hpp"

#include "HMUI/Touchable.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Networking/DownloadHandler.hpp"
#include "UnityEngine/Networking/DownloadHandlerTexture.hpp"
#include "UnityEngine/Networking/UnityWebRequest.hpp"
#include "UnityEngine/Networking/UnityWebRequestTexture.hpp"

#include "Data/Creators.hpp"

#include "Utils/RainbowUtils.hpp"
#include "Utils/ZipUtils.hpp"

#include "assets.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/Helpers/getters.hpp"
#include "bsml/shared/Helpers/utilities.hpp"
#include "logging.hpp"

DEFINE_TYPE(Qosmetics::Core, QosmeticObjectTableCell);

using namespace UnityEngine;
using namespace UnityEngine::UI;

UnityEngine::Color highlightedColor = UnityEngine::Color(0.0f, 0.0f, 0.5f, 0.8f);
UnityEngine::Color idleColor = UnityEngine::Color(0.0f, 0.0f, 0.0f, 0.8f);

namespace Qosmetics::Core
{
    Qosmetics::Core::QosmeticObjectTableCell* QosmeticObjectTableCell::CreateNewCell()
    {
        static ConstString playerTableCellStr("GlobalLeaderboardTableCell");
        auto cellGO = UnityEngine::GameObject::New_ctor();
        auto playerCell = cellGO->AddComponent<QosmeticObjectTableCell*>();
        cellGO->set_name(playerTableCellStr);

        BSML::parse_and_construct(Assets::QosmeticsItemCell_bsml, cellGO->get_transform(), playerCell);
        return playerCell;
    }

    void QosmeticObjectTableCell::PostParse()
    {
        get_gameObject()->AddComponent<HMUI::Touchable*>();
        hover = get_gameObject()->GetComponent<HMUI::HoverHint*>();
        if (!hover)
            hover = get_gameObject()->AddComponent<HMUI::HoverHint*>();
        hover->set_text("---");
        hover->_hoverHintController = BSML::Helpers::GetHoverHintController();
        image->_skew = 0.18f;

        backgroundImage->background->set_color(idleColor);
        backgroundImage->background->set_color0({1.0f, 1.0f, 1.0f, 1.0f});
        backgroundImage->background->set_color1({1.0f, 1.0f, 1.0f, 1.0f});
    }

    void QosmeticObjectTableCell::HighlightDidChange(HMUI::SelectableCell::TransitionType transitionType)
    {
        backgroundImage->background->set_color(get_highlighted() ? highlightedColor : idleColor);
    }

    void QosmeticObjectTableCell::Select()
    {
        if (onSelect)
            onSelect(this);
    }

    void QosmeticObjectTableCell::AttemptDelete()
    {
        deletionConfirmationModal->Show(this);
    }

    void QosmeticObjectTableCell::Delete()
    {
        if (onDelete)
            onDelete(this);
    }

    void QosmeticObjectTableCell::SetDescriptor(Descriptor descriptor)
    {
        this->descriptor = descriptor;
        set_name(descriptor.get_name());
        set_sub(descriptor.get_author());
        set_hover(descriptor.get_description());
        auto coverImage = descriptor.get_coverImage();
        DEBUG("Got Cover image {} for object {}", descriptor.get_coverImage(), descriptor.get_name());
        if (coverImage != "")
            LoadPreviewImage();
        else
            set_sprite(tableData->DefaultSprite());
    }

    void QosmeticObjectTableCell::set_name(std::string_view nameText)
    {
        if (RainbowUtils::shouldRainbow(nameText))
            this->name->set_text(RainbowUtils::rainbowify(nameText));
        else
            this->name->set_text(nameText);
    }

    void QosmeticObjectTableCell::set_sub(std::string_view subText)
    {
        auto color = Creators::GetCreatorColor(std::string(subText));
        if (RainbowUtils::shouldRainbow(color))
        {
            sub->set_text(RainbowUtils::rainbowify(subText));
        }
        else
        {
            sub->set_text(subText);
        }
        sub->set_color(color);
    }

    void QosmeticObjectTableCell::set_hover(std::string_view hoverText)
    {
        hover->set_text(fmt::format("<i>{}</i>", hoverText));
    }

    void QosmeticObjectTableCell::set_sprite(UnityEngine::Sprite* sprite)
    {
        image->set_sprite(sprite);
    }

    custom_types::Helpers::Coroutine QosmeticObjectTableCell::DownloadPreviewImage()
    {
        UnityEngine::Networking::UnityWebRequest* www = UnityEngine::Networking::UnityWebRequestTexture::GetTexture(descriptor.get_coverImage());
        co_yield reinterpret_cast<System::Collections::IEnumerator*>(www->SendWebRequest());
        auto downloadHandlerTexture = reinterpret_cast<UnityEngine::Networking::DownloadHandlerTexture*>(www->get_downloadHandler());
        auto texture = downloadHandlerTexture->get_texture();
        auto sprite = BSML::Utilities::LoadSpriteFromTexture(texture);
        tableData->AddCachedSprite(descriptor.get_filePath(), sprite);
        set_sprite(sprite);
        co_return;
    }

    void QosmeticObjectTableCell::LoadPreviewImage()
    {
        // check if image already cached
        auto sprite = tableData->GetCachedSprite(descriptor.get_filePath());
        if (sprite && sprite->m_CachedPtr)
        {
            set_sprite(sprite);
            return;
        }

        // check to see if it's a url
        if (descriptor.get_coverImage().find("http") != std::string::npos)
        {
            DEBUG("Image was url, downloading texture...");
            StartCoroutine(custom_types::Helpers::CoroutineHelper::New(DownloadPreviewImage()));
            return;
        }

        // else just load the image from the zip
        ArrayW<uint8_t> bytes;
        if (ZipUtils::GetBytesFromZipFile(descriptor.get_filePath(), descriptor.get_coverImage(), bytes))
        {
            auto sprite = BSML::Utilities::LoadSpriteRaw(bytes);
            tableData->AddCachedSprite(descriptor.get_filePath(), sprite);
            set_sprite(sprite);
        }
        else // if all fails, just set the default sprite
        {
            set_sprite(tableData->DefaultSprite());
        }
    }
}

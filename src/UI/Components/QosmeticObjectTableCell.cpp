#include "UI/Components/QosmeticObjectTableCell.hpp"
#include "diglett/shared/Localization.hpp"
#include "diglett/shared/Util.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

#include "HMUI/Touchable.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Networking/DownloadHandler.hpp"
#include "UnityEngine/Networking/DownloadHandlerTexture.hpp"
#include "UnityEngine/Networking/UnityWebRequest.hpp"
#include "UnityEngine/Networking/UnityWebRequestTexture.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/SpriteMeshType.hpp"
#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"

#include "Data/Creators.hpp"

#include "Utils/RainbowUtils.hpp"
#include "Utils/ZipUtils.hpp"

#include "assets.hpp"
#include "logging.hpp"

DEFINE_TYPE(Qosmetics::Core, QosmeticObjectTableCell);

using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace QuestUI::BeatSaberUI;

#define SetHorizontalFitMode(obj, mode)                                               \
    auto obj##SizeFitter = obj->get_gameObject()->GetComponent<ContentSizeFitter*>(); \
    if (!obj##SizeFitter)                                                             \
        obj##SizeFitter = obj->get_gameObject()->AddComponent<ContentSizeFitter*>();  \
    obj##SizeFitter->set_horizontalFit(mode)
UnityEngine::Color highlightedColor = UnityEngine::Color(0.0f, 0.0f, 0.5f, 0.8f);
UnityEngine::Color idleColor = UnityEngine::Color(0.0f, 0.0f, 0.0f, 0.8f);
VerticalLayoutGroup* CreateHost(Transform* parent, Vector2 anchoredPos,
                                Vector2 size)
{
    VerticalLayoutGroup* group = CreateVerticalLayoutGroup(parent);
    group->get_rectTransform()->set_anchoredPosition(anchoredPos);

    LayoutElement* elem = group->GetComponent<LayoutElement*>();
    elem->set_preferredHeight(size.y);
    elem->set_preferredWidth(size.x);

    ContentSizeFitter* fitter = group->GetComponent<ContentSizeFitter*>();
    fitter->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
    fitter->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);
    return group;
}

namespace Qosmetics::Core
{
    Qosmetics::Core::QosmeticObjectTableCell* QosmeticObjectTableCell::CreateNewCell()
    {
        static ConstString playerTableCellStr("GlobalLeaderboardTableCell");
        auto cellGO = UnityEngine::GameObject::New_ctor();
        auto playerCell = cellGO->AddComponent<QosmeticObjectTableCell*>();
        cellGO->set_name(playerTableCellStr);
        playerCell->Setup();
        return playerCell;
    }

    void QosmeticObjectTableCell::Setup()
    {
        get_gameObject()->AddComponent<HMUI::Touchable*>();
        auto bgHost = CreateHost(get_transform(), {0.0f, 0}, {100.0f, 12.0f});
        auto bg = bgHost->get_gameObject()->AddComponent<QuestUI::Backgroundable*>();
        bg->ApplyBackgroundWithAlpha("title-gradient", 0.8f);
        backgroundImage = bg->get_gameObject()->GetComponentInChildren<HMUI::ImageView*>();
        backgroundImage->set_color(idleColor);
        backgroundImage->set_color0({1.0f, 1.0f, 1.0f, 1.0f});
        backgroundImage->set_color1({1.0f, 1.0f, 1.0f, 1.0f});

        auto imageHost = CreateHost(get_transform(), {-42.5f, 0}, {9.0f, 9.0f});
        image = CreateImage(imageHost->get_transform(), nullptr, {0, 0}, {0, 0});
        image->skew = 0.18f;

        auto textHost = CreateHost(get_transform(), {-5.0f, 0}, {62.5f, 12.0f});
        textHost->set_childAlignment(UnityEngine::TextAnchor::MiddleLeft);
        name = CreateText(textHost->get_transform(), "---", {0, 0}, {0, 0});
        sub = CreateText(textHost->get_transform(), "---", {0, 0}, {0, 0});

        // auto selectBtn = CreateClickableImage(CreateHost(get_transform(), {32.5f, 0}, {8.0f, 8.0f})->get_transform(), VectorToSprite(std::vector<uint8_t>(_binary_SelectIcon_png_start, _binary_SelectIcon_png_end)), Vector2(0, 0), Vector2(0, 0), std::bind(&QosmeticObjectTableCell::Select, this));
        // selectBtn->skew = 0.18f;
        // selectBtn->set_highlightColor({0.2f, 0.8f, 0.2f, 1.0f});
        auto deleteBtn = CreateClickableImage(CreateHost(get_transform(), {42.5f, 0}, {6.0f, 6.0f})->get_transform(), VectorToSprite(std::vector<uint8_t>(_binary_DeleteIcon_png_start, _binary_DeleteIcon_png_end)), Vector2(0, 0), Vector2(0, 0), std::bind(&QosmeticObjectTableCell::AttemptDelete, this));
        deleteBtn->set_highlightColor({0.8f, 0.2f, 0.2f, 1.0f});
        deleteBtn->skew = 0.18f;

        hover = AddHoverHint(get_gameObject(), "---");
    }

    void QosmeticObjectTableCell::HighlightDidChange(HMUI::SelectableCell::TransitionType transitionType)
    {
        backgroundImage->set_color(get_highlighted() ? highlightedColor : idleColor);
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
        deletionConfirmationModal->Hide(true, nullptr);
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

    void QosmeticObjectTableCell::set_name(std::string_view name)
    {
        if (RainbowUtils::shouldRainbow(name))
            this->name->set_text(u"<i>" + to_utf16(RainbowUtils::rainbowify(name)) + u"</i>");
        else
            this->name->set_text(u"<i>" + to_utf16(name) + u"</i>");
    }

    void QosmeticObjectTableCell::set_sub(std::string_view sub)
    {
        auto color = Creators::GetCreatorColor(std::string(sub));
        if (RainbowUtils::shouldRainbow(color))
        {
            this->sub->set_text(u"<i>" + to_utf16(RainbowUtils::rainbowify(sub)) + u"</i>");
        }
        else
        {
            this->sub->set_text(u"<i>" + to_utf16(sub) + u"</i>");
        }
        this->sub->set_color(color);
    }

    void QosmeticObjectTableCell::set_hover(std::string_view hover)
    {
        this->hover->set_text(u"<i>" + to_utf16(hover) + u"</i>");
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
        auto sprite = Sprite::Create(texture, Rect(0.0f, 0.0f, (float)texture->get_width(), (float)texture->get_height()), Vector2(0.5f, 0.5f), 1024.0f, 1u, SpriteMeshType::FullRect, Vector4(0.0f, 0.0f, 0.0f, 0.0f), false);
        tableData->AddCachedSprite(descriptor.get_filePath(), sprite);
        set_sprite(sprite);
        co_return;
    }

    void QosmeticObjectTableCell::LoadPreviewImage()
    {
        // check if image already cached
        auto sprite = tableData->GetCachedSprite(descriptor.get_filePath());
        if (sprite)
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
        std::vector<uint8_t> bytes;
        if (ZipUtils::GetBytesFromZipFile(descriptor.get_filePath(), descriptor.get_coverImage(), bytes))
        {
            auto sprite = VectorToSprite(bytes);
            tableData->AddCachedSprite(descriptor.get_filePath(), sprite);
            set_sprite(sprite);
        }
        else // if all fails, just set the default sprite
        {
            set_sprite(tableData->DefaultSprite());
        }
    }
}
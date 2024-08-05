#include "UI/Components/QosmeticObjectTableCell.hpp"

#include "HMUI/Touchable.hpp"
#include "UnityEngine/GameObject.hpp"

#include "Data/Creators.hpp"

#include "Utils/RainbowUtils.hpp"
#include "Utils/ZipUtils.hpp"

#include "assets.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSML/MainThreadScheduler.hpp"
#include "bsml/shared/Helpers/getters.hpp"
#include "bsml/shared/Helpers/utilities.hpp"
#include "logging.hpp"
#include "web-utils/shared/WebUtils.hpp"

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

    void QosmeticObjectTableCell::PostParse() {
        gameObject->AddComponent<HMUI::Touchable*>();
        _hover = gameObject->GetComponent<HMUI::HoverHint*>();
        if (!_hover)
            _hover = gameObject->AddComponent<HMUI::HoverHint*>();

        _hover->text = "---";
        _hover->_hoverHintController = BSML::Helpers::GetHoverHintController();
        _image->_skew = 0.18f;

        _backgroundImage->background->color = idleColor;
        _backgroundImage->background->color0 = {1.0f, 1.0f, 1.0f, 1.0f};
        _backgroundImage->background->color1 = {1.0f, 1.0f, 1.0f, 1.0f};
    }

    void QosmeticObjectTableCell::HighlightDidChange(HMUI::SelectableCell::TransitionType transitionType) {
        _backgroundImage->background->set_color(highlighted ? highlightedColor : idleColor);
    }

    void QosmeticObjectTableCell::Select() {
        if (onSelect)
            onSelect(this);
    }

    void QosmeticObjectTableCell::AttemptDelete() {
        _deletionConfirmationModal->Show(this);
    }

    void QosmeticObjectTableCell::Delete()
    {
        if (onDelete)
            onDelete(this);
    }

    void QosmeticObjectTableCell::SetDescriptor(Descriptor const& descriptor) {
        this->descriptor = descriptor;
        name = descriptor.get_name();
        sub = descriptor.get_author();
        hover = descriptor.get_description();

        auto coverImage = descriptor.coverImage;
        DEBUG("Got Cover image {} for object {}", coverImage, descriptor.get_name());
        if (coverImage.empty())
            sprite = _tableData->DefaultSprite();
        else
            LoadPreviewImage();
    }

    void QosmeticObjectTableCell::set_name(std::string_view nameText) {
        if (RainbowUtils::shouldRainbow(nameText))
            this->_name->text = RainbowUtils::rainbowify(nameText);
        else
            this->_name->text = nameText;
    }

    void QosmeticObjectTableCell::set_sub(std::string_view subText) {
        auto color = Creators::GetCreatorColor(std::string(subText));
        if (RainbowUtils::shouldRainbow(color))
            _sub->text = RainbowUtils::rainbowify(subText);
        else
            _sub->text = subText;
        _sub->color = color;
    }

    void QosmeticObjectTableCell::set_hover(std::string_view hoverText) {
        _hover->text = fmt::format("<i>{}</i>", hoverText);
    }

    void QosmeticObjectTableCell::set_sprite(UnityEngine::Sprite* sprite) {
        _image->sprite = sprite;
    }

    void QosmeticObjectTableCell::LoadPreviewImage() {
        // check if image already cached
        auto sprite = _tableData->GetCachedSprite(descriptor.filePath);
        if (sprite && sprite->m_CachedPtr.m_value) {
            this->sprite = sprite;
            return;
        }

        // check to see if it's a url
        if (descriptor.coverImage.find("http") != std::string::npos) {
            BSML::MainThreadScheduler::AwaitFuture<WebUtils::SpriteResponse>(
                WebUtils::GetAsync<WebUtils::SpriteResponse>({descriptor.coverImage}),
                [descriptor = this->descriptor, image = this->_image, tableData = this->_tableData](auto response) {
                    if (response.IsSuccessful() && response.DataParsedSuccessful()) {
                        auto sprite = response.responseData.value();
                        tableData->AddCachedSprite(descriptor.get_filePath(), sprite);
                        image->set_sprite(sprite);
                    }
                }
            );
            return;
        }

        // else just load the image from the zip
        ArrayW<uint8_t> bytes;
        if (ZipUtils::GetBytesFromZipFile(descriptor.filePath, descriptor.coverImage, bytes)) {
            auto sprite = BSML::Utilities::LoadSpriteRaw(bytes);
            _tableData->AddCachedSprite(descriptor.filePath, sprite);
            this->sprite = sprite;
        } else { // if all fails, just set the default sprite
            this->sprite = _tableData->DefaultSprite();
        }
    }
}

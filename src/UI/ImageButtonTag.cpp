#include "UI/ImageButtonTag.hpp"
#include "logging.hpp"

#include "bsml/shared/BSML/Components/ExternalComponents.hpp"

#include "Polyglot/LocalizedTextMeshProUGUI.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/UI/LayoutGroup.hpp"

#include "HMUI/ButtonSpriteSwap.hpp"

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace Qosmetics::Core
{
    static BSML::BSMLNodeParser<ImageButtonTag> imageButtonTagParser({"image-button"});
    Button* ImageButtonTag::get_buttonPrefab() const
    {
        static SafePtrUnity<Button> buttonPrefab;
        if (!buttonPrefab)
        {
            buttonPrefab = Resources::FindObjectsOfTypeAll<Button*>().LastOrDefault([&](auto x)
                                                                                    { return x->get_name() == "SettingsButton"; });
        }
        return buttonPrefab.ptr();
    }

    GameObject* ImageButtonTag::CreateObject(Transform* parent) const
    {
        DEBUG("Creating ImageButton: {}", fmt::ptr(get_buttonPrefab()));
        auto button = Object::Instantiate(get_buttonPrefab(), parent, false);
        button->set_name("BSMLButton");
        button->set_interactable(true);

        auto transform = reinterpret_cast<RectTransform*>(button->get_transform());
        auto gameObject = button->get_gameObject();
        gameObject->SetActive(true);
        auto externalComponents = gameObject->AddComponent<BSML::ExternalComponents*>();
        externalComponents->Add(button);
        externalComponents->Add(transform);

        auto textObject = button->get_transform()->Find("Text")->get_gameObject();
        auto localizedText = textObject->GetComponent<Polyglot::LocalizedTextMeshProUGUI*>();
        if (localizedText)
            Object::Destroy(localizedText);

        auto textMesh = textObject->GetComponent<TMPro::TextMeshProUGUI*>();
        textMesh->set_text("BSMLButton");
        textMesh->set_richText(true);
        externalComponents->Add(textMesh);

        auto buttonSizeFitter = gameObject->AddComponent<ContentSizeFitter*>();
        buttonSizeFitter->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
        buttonSizeFitter->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);
        externalComponents->Add(buttonSizeFitter);

        auto stackLayoutGroup = button->GetComponentInChildren<LayoutGroup*>();
        if (stackLayoutGroup)
            externalComponents->Add(stackLayoutGroup);

        auto layoutElement = gameObject->AddComponent<LayoutElement*>();
        layoutElement->set_preferredWidth(30.0f);
        externalComponents->Add(layoutElement);

        auto spriteSwap = gameObject->GetComponentInChildren<HMUI::ButtonSpriteSwap*>();
        if (spriteSwap)
            externalComponents->Add(spriteSwap);

        return gameObject;
    }

}
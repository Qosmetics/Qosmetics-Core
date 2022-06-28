#include "Data/Creators.hpp"
#include "UI/QosmeticsFlowCoordinator.hpp"
#include "assets.hpp"
#include "diglett/shared/Localization.hpp"
#include "diglett/shared/Util.hpp"
#include "hooks.hpp"
#include "logging.hpp"
#include "questui/shared/ArrayUtil.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

#include "GlobalNamespace/OptionsViewController.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "Polyglot/LocalizedTextMeshProUGUI.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "UnityEngine/Resources.hpp"

using namespace QuestUI;
using namespace QuestUI::BeatSaberUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;

void PresentQosmeticsFlowCoordinator()
{
    auto fc = GetMainFlowCoordinator()->YoungestChildFlowCoordinatorOrSelf();

    auto qfc = ArrayUtil::First(Resources::FindObjectsOfTypeAll<Qosmetics::Core::QosmeticsFlowCoordinator*>());
    if (!qfc)
        qfc = CreateFlowCoordinator<Qosmetics::Core::QosmeticsFlowCoordinator*>();

    fc->PresentFlowCoordinator(qfc, nullptr, HMUI::ViewController::AnimationDirection::Horizontal, false, false);
}

MAKE_AUTO_HOOK_MATCH(OptionsViewController_DidActivate, &GlobalNamespace::OptionsViewController::DidActivate, void, GlobalNamespace::OptionsViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    OptionsViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    if (firstActivation)
    {
        Qosmetics::Core::Creators::Download();

        bool questUIExists = QuestUI::GetModsCount() > 0;
        Button* baseButton = self->dyn__settingsButton();
        Button* button = Object::Instantiate(baseButton);
        button->set_name("Qosmetics Settings");

        UnityEngine::Transform* wrapper = self->get_transform()->Find("Wrapper");
        button->get_transform()->SetParent(wrapper, false);

        if (questUIExists)
        {
            HorizontalLayoutGroup* layout = CreateHorizontalLayoutGroup(self->get_transform());

            Transform* layoutTransform = layout->get_transform();
            self->dyn__editAvatarButton()->get_transform()->SetParent(layoutTransform);
            self->dyn__playerOptionsButton()->get_transform()->SetParent(layoutTransform);
            self->dyn__settingsButton()->get_transform()->SetParent(layoutTransform);

            layoutTransform->SetAsFirstSibling();
            layout->set_spacing(-64.0f);
            layout->get_gameObject()->GetComponent<UnityEngine::RectTransform*>()->set_anchoredPosition(UnityEngine::Vector2(0.0f, -7.5f));

            HorizontalLayoutGroup* oldLayout = wrapper->get_gameObject()->GetComponent<HorizontalLayoutGroup*>();
            oldLayout->get_gameObject()->GetComponent<RectTransform*>()->set_anchoredPosition(UnityEngine::Vector2(0.0f, 0.0f));
            button->get_transform()->SetAsLastSibling();
        }
        else
            button->get_transform()->SetAsFirstSibling();

        button->get_onClick()->AddListener(il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction*>(classof(UnityEngine::Events::UnityAction*), (Il2CppObject*)nullptr, PresentQosmeticsFlowCoordinator));

        SetButtonSprites(button, VectorToSprite(std::vector<uint8_t>(MenuIcon_png::getData(), MenuIcon_png::getData() + MenuIcon_png::getLength())), VectorToSprite(std::vector<uint8_t>(MenuIconSelected_png::getData(), MenuIconSelected_png::getData() + MenuIconSelected_png::getLength())));

        UnityEngine::Object::Destroy(button->GetComponentInChildren<Polyglot::LocalizedTextMeshProUGUI*>());

        button->GetComponentInChildren<TMPro::TextMeshProUGUI*>()->SetText(Diglett::Localization::get_instance()->get("QosmeticsCore:Settings:QosmeticsSettings"));
    }
}
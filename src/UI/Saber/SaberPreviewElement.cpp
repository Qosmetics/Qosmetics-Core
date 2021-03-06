#include "UI/Saber/SaberPreviewElement.hpp"

DEFINE_TYPE(Qosmetics::UI, SaberPreviewElement);

#include "HMUI/Touchable.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/ExternalComponents.hpp"
#include "questui/shared/CustomTypes/Data/CustomDataType.hpp"

#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "UnityEngine/Events/UnityAction_1.hpp"
#include "UnityEngine/WaitUntil.hpp"
#include "System/Collections/IEnumerator.hpp"
#include "System/Func_1.hpp"

#include "Utils/SaberUtils.hpp"

using namespace HMUI;
using namespace UnityEngine;
using namespace UnityEngine::Events;
using namespace UnityEngine::UI;
using namespace QuestUI;
using namespace QuestUI::BeatSaberUI;
using namespace Qosmetics;
using namespace Qosmetics::UI;
using namespace TMPro;

#define INFO(value...) QosmeticsLogger::GetContextLogger("Saber Preview Element").info(value);
#define ERROR(value...) QosmeticsLogger::GetContextLogger("Saber Preview Element").error(value);

namespace Qosmetics::UI
{
    void SaberPreviewElement::Init(SaberManager* modelManager, ColorManager* colorManager)
    {
        this->modelManager = modelManager;
        this->colorManager = colorManager;

        get_transform()->set_localScale(Vector3::get_one() * 50.0f);
        get_transform()->set_localPosition(UnityEngine::Vector3(-30.0f, 0.0f, -75.0f));
        get_transform()->set_localEulerAngles(UnityEngine::Vector3(0.0f, 330.0f, 0.0f));
    }

    void SaberPreviewElement::UpdatePreview(bool reinstantiate)
    {
        INFO("Updating Preview Element");
        if (reinstantiate || !prefab)
        {
            ClearPreview();
            if (!modelManager) return;
            GameObject* prefabToInstantiate = modelManager->GetActivePrefab();
            if (!prefabToInstantiate) return;
            prefab = Instantiate(prefabToInstantiate, get_transform());
            prefab->SetActive(true);
        }
        
        Transform* prefabTransform = prefab->get_transform();
        int childCount = prefabTransform->get_childCount();
        Color leftColor = colorManager->ColorForSaberType(0);
        Color rightColor = colorManager->ColorForSaberType(1);
        for (int i = 0; i < childCount; i++)
        {
            Transform* child = prefabTransform->GetChild(i);

            std::string name = to_utf8(csstrtostr(child->get_gameObject()->get_name()));
            //INFO("Found Child %s", name.c_str());
            if (name == "LeftSaber")
            {
                child->set_localPosition(UnityEngine::Vector3(0.0f, 0.25f, -0.4f));
                SaberUtils::SetColors(child->get_gameObject(), leftColor, rightColor);
            }
            else if (name == "RightSaber")
            {
                child->set_localPosition(UnityEngine::Vector3(0.0f, -0.25f, -0.4f));
                SaberUtils::SetColors(child->get_gameObject(), rightColor, leftColor);
            }
            else Object::Destroy(child);
        }
    }

    void SaberPreviewElement::ClearPreview()
    {
        if (prefab) Object::Destroy(prefab);
        prefab = nullptr;
    }
}
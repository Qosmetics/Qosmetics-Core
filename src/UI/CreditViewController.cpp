#include "UI/CreditViewController.hpp"
#include "Data/Patrons.hpp"
#include "Utils/DateUtils.hpp"
#include "Utils/RainbowUtils.hpp"
#include "Utils/UIUtils.hpp"
#include "logging.hpp"
#include "static-defines.hpp"

#include "GlobalNamespace/SharedCoroutineStarter.hpp"

#include "assets.hpp"
#include "bsml/shared/BSML.hpp"

#include "HMUI/Touchable.hpp"

#include "UnityEngine/Application.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Networking/DownloadHandler.hpp"
#include "UnityEngine/Networking/UnityWebRequest.hpp"
#include "UnityEngine/Networking/UnityWebRequestAsyncOperation.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Shader.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"

DEFINE_TYPE(Qosmetics::Core, CreditViewController);
DEFINE_TYPE(Qosmetics::Core, Patron);
DEFINE_TYPE(Qosmetics::Core, Tier);

using namespace UnityEngine;
using namespace UnityEngine::UI;

std::string repeat(char c, int count)
{
    std::string res;
    res.reserve(count);
    for (int i = 0; i < count; i++)
        res += c;
    return res;
}

namespace Qosmetics::Core
{
    StringW CreditViewController::get_thankyou()
    {
        return "These Patrons and Donators have donated to show their support,\nand have received a place here to thank them for this.\nThis support is greatly appreciated and will help justify time spent on developing Qosmetics & other mods.\nA massive thanks goes out to all these people!\n\nIf you'd also like to support development, the patreon can be found at:";
    }

    bool CreditViewController::get_gay()
    {
        return DateUtils::isMonth(6);
    }

    StringW CreditViewController::get_gaydient()
    {
        return RainbowUtils::randomGradient();
    }

    void CreditViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (!firstActivation)
            return;
        BSML::parse_and_construct(IncludedAssets::CreditView_bsml, get_transform(), this);
        StartCoroutine(custom_types::Helpers::CoroutineHelper::New(GetPatreonSupporters()));
    }

    custom_types::Helpers::Coroutine CreditViewController::GetPatreonSupporters()
    {
        UnityEngine::Networking::UnityWebRequest* www = UnityEngine::Networking::UnityWebRequest::Get(patron_url);
        auto req = www->SendWebRequest();
        co_yield reinterpret_cast<System::Collections::IEnumerator*>(req);

        bool isHttpError = www->get_isHttpError();
        bool isNetworkError = www->get_isNetworkError();

        if (isHttpError || isNetworkError)
        {
            ERROR("Failed to fetch patrons file from resources repository");
            ERROR("Was http error: {}", isHttpError);
            ERROR("Was network error: {}", isNetworkError);

            placeholderText->set_text("There were no patrons found, There must have been a network error!");
            co_return;
        }

        auto downloadHandler = www->get_downloadHandler();
        auto patrons = Qosmetics::Core::Patrons::Parse(static_cast<std::string>(downloadHandler->get_text()));

        if (!patrons.any())
        {
            placeholderText->set_text("There were no patrons found, you can be the first to appear here!");
        }
        else
        {
            auto scrollViewContentContainer = patronTexts->get_parent()->get_parent();
            Object::DestroyImmediate(patronTexts->get_parent()->get_gameObject());
            if (!patrons.legendary.empty())
            {
                auto tier = Tier::New_ctor("<color=#000000>Legendary patrons</color> <color=#222222><size=2>(Tier 4)</size></color>", Color(0.9f, 0.75f, 0.25f, 1.0f));
                for (auto patron : patrons.legendary)
                    tier->patrons->Add(Patron::New_ctor(patron));

                BSML::parse_and_construct(IncludedAssets::PatronCreditBox_bsml, scrollViewContentContainer, tier);

                auto bannerimageView = tier->banner->background;
                auto origMat = UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::Material*>().FirstOrDefault(
                    [](UnityEngine::Material* x)
                    {
                        return x->get_name() == "AnimatedButton";
                    });
                auto dupe = Object::Instantiate(origMat);
                dupe->SetColor(Shader::PropertyToID("_ShineColor"), Color(0.9f, 0.75f, 0.25f, 1.0f));
                bannerimageView->set_material(dupe);

                tier->Finalize();
            }

            if (!patrons.amazing.empty())
            {
                auto tier = Tier::New_ctor("<color=#000000>Amazing patrons</color> <color=#222222><size=2>(Tier 3)</size></color>", Color(0.4f, 0.45f, 0.8f, 1.0f));
                for (auto patron : patrons.amazing)
                    tier->patrons->Add(Patron::New_ctor(patron));

                BSML::parse_and_construct(IncludedAssets::PatronCreditBox_bsml, scrollViewContentContainer, tier);
                tier->Finalize();
            }

            if (!patrons.enthusiastic.empty())
            {
                auto tier = Tier::New_ctor("<color=#000000>Enthusiastic patrons</color> <color=#222222><size=2>(Tier 2)</size></color>", Color(0.5f, 0.55f, 0.9f, 1.0f));
                for (auto patron : patrons.enthusiastic)
                    tier->patrons->Add(Patron::New_ctor(patron));

                BSML::parse_and_construct(IncludedAssets::PatronCreditBox_bsml, scrollViewContentContainer, tier);
                tier->Finalize();
            }

            if (!patrons.paypal.empty())
            {
                auto tier = Tier::New_ctor("<color=#000000>Paypal donators</color>", Color(0.0f, 0.6f, 0.85f, 1.0f));
                for (auto patron : patrons.paypal)
                    tier->patrons->Add(Patron::New_ctor(patron));

                BSML::parse_and_construct(IncludedAssets::PatronCreditBox_bsml, scrollViewContentContainer, tier);
                tier->Finalize();
            }
        }
        co_return;
    }

    void Patron::ctor(StringW patronName)
    {
        this->patronName = patronName;
    }

    void Tier::ctor(StringW tierName, UnityEngine::Color bannerColor)
    {
        this->tierName = tierName;
        this->bannerColor = bannerColor;
        patrons = List<Patron*>::New_ctor();
    }

    void Tier::PostParse()
    {
        HMUI::ImageView* imageView = banner->background;
        imageView->gradient = true;
        imageView->gradientDirection = 1;
        imageView->set_color(bannerColor);
        imageView->set_color0(Color(1.1f, 1.1f, 1.1f, 1.0f));
        imageView->set_color1(Color(0.9f, 0.9f, 0.9f, 1.0f));
    }

}
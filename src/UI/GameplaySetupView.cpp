#include "UI/GameplaySetupView.hpp"
#include "logging.hpp"

#include "assets.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSMLDataCache.hpp"

DEFINE_TYPE(Qosmetics::Core, GameplaySetupView);

using namespace UnityEngine;

namespace Qosmetics::Core
{
    void GameplaySetupView::Inject(QosmeticsFlowCoordinator* qosmeticsFlowCoordinator, ListWrapper<QosmeticsBaseFlowCoordinator*> baseFlowCoordinators)
    {
        this->qosmeticsFlowCoordinator = qosmeticsFlowCoordinator;
        this->flowCoordinators = baseFlowCoordinators;
    }

    bool GameplaySetupView::get_anyCoordinators()
    {
        return flowCoordinators && flowCoordinators.size() > 0;
    }

    void GameplaySetupView::Initialize()
    {
        DEBUG("Initialize");
        BSML::Register::RegisterGameplaySetupTab("Qosmetics", MOD_ID "_gameplaySetupTab", this);
    }

    void GameplaySetupView::Dispose()
    {
        DEBUG("Dispose");
        BSML::Register::UnRegisterGameplaySetupTab("Qosmetics");
    }

    void GameplaySetupView::PostParse()
    {
        if (grid && grid->m_CachedPtr.m_value)
            grid->set_localScale(grid->get_localScale() * 0.66f);
    }
}

BSML_DATACACHE(gameplaySetupTab)
{
    return IncludedAssets::GameplaySetupView_bsml;
}

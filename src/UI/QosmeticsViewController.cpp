#include "UI/QosmeticsViewController.hpp"
#include "assets.hpp"
#include "logging.hpp"

#include "UI/QosmeticsBaseFlowCoordinator.hpp"
#include "bsml/shared/BSML.hpp"

DEFINE_TYPE(Qosmetics::Core, QosmeticsViewController);

namespace Qosmetics::Core {
    void QosmeticsViewController::Inject(ListW<Qosmetics::Core::QosmeticsBaseFlowCoordinator*> baseFlowCoordinators) {
        // this should get all the QosmeticsBaseFlowCoordinators :)
        flowCoordinators = baseFlowCoordinators;
    }

    void QosmeticsViewController::set_qosmeticsFlowCoordinator(HMUI::FlowCoordinator* qosmeticsFlowCoordinator) {
        this->qosmeticsFlowCoordinator = qosmeticsFlowCoordinator;
        if (get_anyCoordinators()) {
            for (auto& fc : flowCoordinators)
                fc->qosmeticsFlowCoordinator = qosmeticsFlowCoordinator;
        }
    }

    bool QosmeticsViewController::get_anyCoordinators() { return flowCoordinators && flowCoordinators.size() > 0; }

    void QosmeticsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (!firstActivation) return;
        BSML::parse_and_construct(Assets::Views::QosmeticsView_bsml, get_transform(), this);
    }
}

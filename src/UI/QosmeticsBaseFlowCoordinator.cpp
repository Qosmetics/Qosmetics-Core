#include "UI/QosmeticsBaseFlowCoordinator.hpp"
#include "logging.hpp"

DEFINE_TYPE(Qosmetics::Core, QosmeticsBaseFlowCoordinator);

void Qosmetics::Core::QosmeticsBaseFlowCoordinator::ctor()
{
    static auto baseKlass = classof(HMUI::FlowCoordinator*);
    custom_types::InvokeBaseCtor(baseKlass, this);
}

void Qosmetics::Core::QosmeticsBaseFlowCoordinator::DidActivate_Base(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    auto didactivate = il2cpp_utils::FindMethodUnsafe(this, "DidActivate", 3);
    if (didactivate)
        il2cpp_utils::RunMethod(this, didactivate, firstActivation, addedToHierarchy, screenSystemEnabling);
}

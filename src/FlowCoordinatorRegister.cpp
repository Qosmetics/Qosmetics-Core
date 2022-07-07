#include "FlowCoordinatorRegister.hpp"
#include "FlowCoordinatorRegister_Internal.hpp"

namespace Qosmetics::Core::FlowCoordinator
{
    std::vector<const Registration*> registrations;
    void Register(const Registration* registration)
    {
        registrations.push_back(registration);

        // we're just sorting this because then the buttons end up in the same order as before the rewrite
        std::sort(registrations.rbegin(), registrations.rend(), [](auto* lhs, auto* rhs) -> bool
                  { return lhs->name < rhs->name; });
    }

    const std::vector<const Registration*>& GetRegistrations()
    {
        return registrations;
    }
}
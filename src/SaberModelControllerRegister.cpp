#include "SaberModelControllerRegister_Internal.hpp"

namespace Qosmetics::Core::SaberModelControllerRegister
{
    std::vector<const SaberModelControllerRegistration*> registrations;

    void Register(const SaberModelControllerRegistration* registration)
    {
        auto existingItr = std::find_if(registrations.begin(), registrations.end(), [&](auto x)
                                        { return x->identifier == registration->identifier; });
        if (existingItr == registrations.end()) // this is a new one!
        {
            registrations.emplace_back(registration);
        }

        // reverse sort so lowest prio is index 0, highest is last
        std::sort(registrations.begin(), registrations.end(), [](auto* lhs, auto* rhs) -> bool
                  { return lhs->operator<(*rhs); });
    }

    bool SaberModelControllerRegistration::operator<(const SaberModelControllerRegistration& rhs) const
    {
        return priority < rhs.priority;
    }

    std::vector<const SaberModelControllerRegistration*>& GetRegistrations() { return registrations; }

}
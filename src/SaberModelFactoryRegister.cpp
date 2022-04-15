#include "SaberModelFactoryRegister_Internal.hpp"

namespace Qosmetics::Core::SaberModelFactoryRegister
{
    std::vector<const SaberModelFactory*> registrations;

    void Register(const SaberModelFactory* registration)
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

    bool SaberModelFactory::operator<(const SaberModelFactory& rhs) const
    {
        return priority < rhs.priority;
    }

    std::vector<const SaberModelFactory*>& GetRegistrations() { return registrations; }

}
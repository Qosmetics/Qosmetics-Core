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

        std::sort(registrations.begin(), registrations.end());
    }

    bool SaberModelFactory::operator<(const SaberModelFactory& rhs) const
    {
        return priority < rhs.priority;
    }

    std::vector<const SaberModelFactory*> GetRegistrations() { return registrations; }

}
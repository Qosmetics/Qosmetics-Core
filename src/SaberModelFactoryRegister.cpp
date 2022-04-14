#include "SaberModelFactoryRegister_Internal.hpp"

namespace Qosmetics::Core::SaberModelFactoryRegister
{
    std::vector<const SaberModelFactory*> registrations;

    void Register(const SaberModelFactory* registration)
    {
        auto registration = std::find_if(registrations.begin(), registrations.end(), [](auto x)
                                         { return x->identifier == registration->identifier; });
    }

    bool SaberModelFactory::operator<(const SaberModelFactory& rhs) const
    {
        return priority < rhs.priority;
    }

    std::vector<const SaberModelFactory*> GetRegistrations() { return registrations; }

}
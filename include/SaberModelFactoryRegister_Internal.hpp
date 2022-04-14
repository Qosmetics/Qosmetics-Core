#pragma once

#include "SaberModelFactoryRegister.hpp"

namespace Qosmetics::Core::SaberModelFactoryRegister
{
    std::vector<const SaberModelFactory*> GetRegistrations();
}

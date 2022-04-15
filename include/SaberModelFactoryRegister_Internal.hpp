#pragma once

#include "SaberModelFactoryRegister.hpp"
#include <vector>

namespace Qosmetics::Core::SaberModelFactoryRegister
{
    std::vector<const SaberModelFactory*>& GetRegistrations();
}

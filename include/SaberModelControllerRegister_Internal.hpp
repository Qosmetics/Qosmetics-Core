#pragma once

#include "SaberModelControllerRegister.hpp"
#include <vector>

namespace Qosmetics::Core::SaberModelControllerRegister
{
    std::vector<const SaberModelControllerRegistration*>& GetRegistrations();
}

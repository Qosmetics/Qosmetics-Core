#pragma once

#include "Zenject/DiContainer.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"

namespace Qosmetics::Core::Redecoration
{
    void Redecorate(Il2CppObject*& object, std::string_view name, System::Type* objectType, System::Type* containerType, Zenject::DiContainer* container);
}
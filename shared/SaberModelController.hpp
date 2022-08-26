#pragma once

#include "GlobalNamespace/ColorManager.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Core, SaberModelController, UnityEngine::MonoBehaviour,
                      DECLARE_INSTANCE_FIELD(GlobalNamespace::ColorManager*, colorManager);
                      /*
                      // make sure to implement this method as it is required for the type to properly register!
                      DECLARE_INSTANCE_METHOD(void, Init, GlobalNamespace::Saber* saber);
                      */
)
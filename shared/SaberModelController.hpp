#pragma once

#include "GlobalNamespace/ColorManager.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(Qosmetics::Core, SaberModelController, UnityEngine::MonoBehaviour,
                      DECLARE_INSTANCE_FIELD(GlobalNamespace::Saber*, saber);
                      DECLARE_INSTANCE_FIELD(GlobalNamespace::ColorManager*, colorManager);
                      /*
                      DECLARE_INSTANCE_METHOD(void, Init, UnityEngine::Transform* parent, GlobalNamespace::Saber* saber);
                      */
)
#pragma once
#include "UnityEngine/Color.hpp"
#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"

namespace Qosmetics::Core::Creators
{
    void ParseCreators(const rapidjson::Document& doc);
    UnityEngine::Color GetCreatorColor(std::string creator);
    void Download();
}
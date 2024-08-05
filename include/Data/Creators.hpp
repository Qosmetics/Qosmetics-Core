#pragma once

#include "UnityEngine/Color.hpp"
#include <string_view>

namespace Qosmetics::Core::Creators {
    /// @brief parses the given string view as a json document and saves all the creator colors
    void ParseCreators(std::string_view str);

    /// @brief gets the color for a specific creator if available, or the default color otherwise
    UnityEngine::Color GetCreatorColor(std::string creator);

    /// @brief starts the download for the creators json
    void TryDownloadCreators();
}

#pragma once

#include "../_config.h"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include <string>
#include <vector>

namespace Qosmetics::Core::ZipUtils
{
    /// @brief gets bytes from a zip file into the passed vector reference
    /// @param zipPath the filePath for the zip
    /// @param fileName which file to get from the zip
    /// @param out the reference to the output vector
    /// @return true if succesful, false otherwise
    QOSMETICS_CORE_EXPORT bool GetBytesFromZipFile(std::string_view zipPath, std::string_view fileName, std::vector<uint8_t>& out);

    /// @brief gets bytes from a zip file into the passed vector reference
    /// @param zipPath the filePath for the zip
    /// @param fileName which file to get from the zip
    /// @param out reference to output ArrayW, does not need to be initialized
    /// @return true if succesful, false otherwise
    QOSMETICS_CORE_EXPORT bool GetBytesFromZipFile(std::string_view zipPath, std::string_view fileName, ArrayW<uint8_t>& out);
}

#include "Utils/ZipUtils.hpp"
#include "beatsaber-hook/shared/utils/utils.h"
#include "logging.hpp"
#include "zip/shared/zip.h"

namespace Qosmetics::Core::ZipUtils
{
    namespace
    {
        bool ReadZipFile(zip* z, std::string_view fileName, std::vector<uint8_t>& out)
        {
            int index = zip_name_locate(z, fileName.data(), 0);

            if (index == -1)
            {
                return false;
                INFO("file '{}' did not exist in zip, are you sure you passed in the right name?", fileName);
            }
            INFO("Reading file '{}'", fileName);
            struct zip_stat st;
            zip_stat_init(&st);
            zip_stat(z, fileName.data(), 0, &st);

            zip_file* f = zip_fopen(z, st.name, 0);
            out.resize(st.size);
            zip_fread(f, out.data(), st.size);
            INFO("Found {} bytes", st.size);
            zip_fclose(f);

            return true;
        }
    }

    bool ReadZipFile(zip* z, std::string_view fileName, ArrayW<uint8_t>& out)
    {
        int index = zip_name_locate(z, fileName.data(), 0);

        if (index == -1)
        {
            return false;
            INFO("file '{}' did not exist in zip, are you sure you passed in the right name?", fileName);
        }
        INFO("Reading file '{}'", fileName);
        struct zip_stat st;
        zip_stat_init(&st);
        zip_stat(z, fileName.data(), 0, &st);

        zip_file* f = zip_fopen(z, st.name, 0);
        out = ArrayW<uint8_t>(static_cast<il2cpp_array_size_t>(st.size));
        zip_fread(f, out.begin(), st.size);
        INFO("Found {} bytes", st.size);
        zip_fclose(f);

        return true;
    }

    bool GetBytesFromZipFile(std::string_view zipPath, std::string_view fileName, std::vector<uint8_t>& out)
    {
        if (zipPath.ends_with("/"))
        {
            ERROR("Path '{}' was a folder path!", zipPath.data());
            return false;
        }

        if (!fileexists(zipPath) && !direxists(zipPath))
        {
            ERROR("Path '{}' did not exist!", zipPath.data());
            return false;
        }
        if (fileName == "")
        {
            ERROR("File Name was empty!");
            return false;
        }

        int err = 0;
        zip* z = zip_open(zipPath.data(), 0, &err);

        if (!ReadZipFile(z, fileName, out))
        {
            zip_close(z);
            return false;
        }
        zip_close(z);
        return true;
    }

    bool GetBytesFromZipFile(std::string_view zipPath, std::string_view fileName, ArrayW<uint8_t>& out)
    {
        if (zipPath.ends_with("/"))
        {
            ERROR("Path '{}' was a folder path!", zipPath.data());
            return false;
        }

        if (!fileexists(zipPath) && !direxists(zipPath))
        {
            ERROR("Path '{}' did not exist!", zipPath.data());
            return false;
        }
        if (fileName == "")
        {
            ERROR("File Name was empty!");
            return false;
        }

        int err = 0;
        zip* z = zip_open(zipPath.data(), 0, &err);

        if (!ReadZipFile(z, fileName, out))
        {
            zip_close(z);
            return false;
        }
        zip_close(z);
        return true;
    }
}
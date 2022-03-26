#pragma once
#include "../Data/BasicConfig.hpp"
#include "../Data/Descriptor.hpp"
#include "../Utils/ZipUtils.hpp"

namespace Qosmetics::Core
{
    /// @tparam T config for the object, requires a default & const rapidjson::Value& ctor
    template <class T = BasicConfig>
    class Manifest
    {
    public:
        Manifest() : filePath(){};
        Manifest(std::string filePath, std::string fileName, const Descriptor& descriptor, const T& config) : filePath(filePath), fileName(fileName), descriptor(descriptor), config(std::make_shared<T>(config)){};

        Manifest(std::string_view filePath) : filePath(filePath)
        {
            std::vector<uint8_t> data = {};
            if (!ZipUtils::GetBytesFromZipFile(filePath, "package.json", data))
                return;
            rapidjson::Document d;
            d.Parse((char*)data.data(), data.size());

            fileName = d["androidFileName"].GetString();
            descriptor = Descriptor(d["descriptor"], filePath);
            config = std::make_shared<T>(d["config"]);
        }

        rapidjson::Document ToJson()
        {
            rapidjson::Document doc;
            doc.SetObject();
            auto& allocator = doc.GetAllocator();
            doc.AddMember("androidFileName", fileName, allocator);
            doc.AddMember("pcFileName", rapidjson::Value("", sizeof(""), allocator), allocator);
            doc.AddMember("descriptor", descriptor.ToJson(allocator), allocator);
            doc.AddMember("config", config->ToJson(allocator), allocator);

            return doc;
        }
        /// @brief returrns a const reference to the filepath string
        virtual const std::string& get_filePath() const
        {
            return filePath;
        }

        /// @brief returns the fileName, will need appending of _platform though
        virtual const std::string& get_fileName() const
        {
            return fileName;
        }

        /// @brief returns a const reference to the descriptor
        virtual const Descriptor& get_descriptor() const
        {
            return descriptor;
        }

        /// @brief returns a const reference to the config
        virtual const T& get_config() const
        {
            return *config;
        }

    protected:
        std::string filePath;
        std::string fileName;
        Descriptor descriptor = Descriptor();
        std::shared_ptr<T> config = std::make_shared<T>();
    };
}
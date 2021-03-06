#pragma once
#include <map>
#include <vector>
#include <string>
#include "Data/Descriptor.hpp"
#include "beatsaber-hook/shared/rapidjson/include/rapidjson/document.h"
typedef std::map<std::string, Qosmetics::Descriptor> Cache;

namespace Qosmetics
{
    class DescriptorCache
    {
        public:
            /// @brief saves the cache to file
            static void Save();

            /// @brief loads the cache from file
            /// @return bool success in finding file & reading something
            static bool Load();

            /// @brief reloads the cache from file
            static void Reload();

            /// @brief Finds the descriptor for fileName
            /// @param fileName the name that will be searched for, needs entire fileName or path!
            /// @return found descriptor, or invalid
            static Descriptor& GetDescriptor(std::string fileName);

            /// @brief Adds the descriptor to the cache
            /// @param descriptor the descriptor to add
            /// @return Descriptor reference to the newly added descriptor
            static Descriptor& AddDescriptorToCache(Descriptor& descriptor);
            
            /// @brief Creates all descriptors from the given folder
            /// @param folderPath the folder in which to look
            static bool DescriptorsFromFolder(std::string folderPath);

            static Cache& GetCache(ItemType cacheType)
            {
                return descriptors[cacheType];
            }
        private:

            /// @brief writes a doc to file
            /// @param d document to write
            static void Write(rapidjson::Document& d);

            /// @brief Clears all the maps
            static void Clear();

            /// @brief Adds descriptor to specific map
            /// @param descriptor the descriptor copied into the map
            /// @param map the map to add to
            /// @return reference to the newly added descriptor (it's NOT the same as the input)
            static Descriptor& AddDescriptorToMap(Descriptor& descriptor, Cache& map);

            /// @brief gets the specified descriptor reference
            /// @param fileName The key for the descriptor maps
            /// @param map
            /// @return reference to teh found descriptor, or invalid
            static Descriptor& GetDescriptorFromMap(std::string& fileName, Cache& map);
            
            /// @brief adds the descriptors from val into the map
            /// @param val the rapidjson value that has the array of descriptors
            /// @param out the map where the output will go
            static void LoadDescriptorsIntoMap(rapidjson::Value& val, Cache& out);
            
            /// @brief turns a given map into a value
            /// @param map the map to turn into value
            /// @param allocator the allocator to use
            /// @return value that can be added to a document
            static rapidjson::Value MapToValue(Cache& map, rapidjson::Document::AllocatorType& allocator);

            static inline std::map<ItemType, Cache> descriptors = {
                { ItemType::saber, {} }, 
                { ItemType::note, {} }, 
                { ItemType::wall, {} }, 
                { ItemType::pointer, {} }, 
                { ItemType::platform, {} }
            };
            /*
                static inline Cache saberDescriptors = {};
                static inline Cache wallDescriptors = {};
                static inline Cache noteDescriptors = {};
                static inline Cache pointerDescriptors = {};
                static inline Cache platformDescriptors = {};
            */
            static inline Descriptor invalid = Descriptor(ItemType::invalid);
    };
}
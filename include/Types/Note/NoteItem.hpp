#pragma once
#include "Types/Qosmetic/QosmeticItem.hpp"
#include "Types/Note/NoteConfig.hpp"

namespace Qosmetics
{
    class NoteItem : public virtual QosmeticItem
    {
        public:
            NoteItem(Descriptor& descriptor, bool load = false) : QosmeticItem(descriptor, load) {};
            
            NoteConfig& get_config()
            {
                return config;
            }

            void ConfigCallback(UnityEngine::TextAsset* textAsset);

        private:
            NoteConfig config = NoteConfig();
    };
}
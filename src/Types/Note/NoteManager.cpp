#include "Config.hpp"

#include "Data/DescriptorCache.hpp"
#include "QosmeticsLogger.hpp"
#include "Types/Note/NoteItem.hpp"
#include "Types/Note/NoteManager.hpp"
#include "UnityEngine/GameObject.hpp"

DEFINE_TYPE(Qosmetics, NoteManager);

#define INFO(value...) QosmeticsLogger::GetContextLogger("Note Manager").info(value)
#define ERROR(value...) QosmeticsLogger::GetContextLogger("Note Manager").error(value)

using namespace UnityEngine;

static inline Il2CppString* leftArrowName = nullptr;
static inline Il2CppString* rightArrowName = nullptr;
static inline Il2CppString* leftDotName = nullptr;
static inline Il2CppString* rightDotName = nullptr;
static inline Il2CppString* leftDebrisName = nullptr;
static inline Il2CppString* rightDebrisName = nullptr;
static inline Il2CppString* bombName = nullptr;

#define GetNameInPrefab(name)                                \
    if (!activeItem)                                         \
        return nullptr;                                      \
    GameObject* prefab = activeItem->get_prefab();           \
    if (!prefab)                                             \
        return nullptr;                                      \
    Transform* object = prefab->get_transform()->Find(name); \
    if (!object)                                             \
        return nullptr;                                      \
    return UnityEngine::Object::Instantiate(object)

namespace Qosmetics
{
    void NoteManager::ctor()
    {
        this->activeItem = nullptr;
        if (config.lastActiveNote != "")
        {
            Descriptor& descriptor = DescriptorCache::GetDescriptor(config.lastActiveNote);
            if (descriptor.isValid() && fileexists(descriptor.get_filePath()))
            {
                SetActiveNote(config.lastActiveNote, true);
                return;
            }
        }
        SetDefault();
    }

    GameObject* NoteManager::GetActivePrefab()
    {
        if (!activeItem)
            return nullptr;
        return activeItem->get_prefab();
    }

    void NoteManager::SetActiveModel(Il2CppString* csname)
    {
        if (!csname)
            return;
        std::string name = to_utf8(csstrtostr(csname));
        internalSetActiveModel(name, true);
    }

    void NoteManager::FromFilePath(std::string path, bool load)
    {
        if (getenv("notelocked"))
            return;
        if (this->activeItem && this->activeItem->get_descriptor().get_filePath() == path)
            return;

        Descriptor* desc = new Descriptor(path);

        // if descriptor doesn't exist for this thing, ignore the setactive
        if (!desc->isValid())
        {
            ERROR("Item was invalid!");
            return;
        }

        if (this->activeItem)
            delete (this->activeItem);
        this->activeItem = new NoteItem(*desc, false);
        if (load)
            this->activeItem->Load();
        INFO("Active Item Set!");
    }

    void NoteManager::SetDefault()
    {
        if (activeItem)
            delete (activeItem);
        activeItem = new NoteItem(DescriptorCache::GetDescriptor(""));
    }

    void NoteManager::internalSetActiveModel(std::string name, bool load)
    {
        INFO("Setting active Note %s", name.c_str());
        // if new set is already the active one, ignore
        if (activeItem && activeItem->get_descriptor().GetFileName() == name)
            return;
        Descriptor& newItem = DescriptorCache::GetDescriptor(name);
        // if descriptor doesn't exist for this thing, ignore the setactive
        if (!newItem.isValid())
        {
            ERROR("Item was invalid!");
            return;
        }
        if (activeItem)
            delete (activeItem);
        activeItem = new NoteItem(newItem, false);
        if (load)
            activeItem->Load();
        INFO("Active Item Set!");
    }

    void NoteManager::SetActiveNote(std::string name, bool load)
    {
        internalSetActiveModel(name, load);
    }

    NoteItem& NoteManager::get_item()
    {
        CRASH_UNLESS(activeItem);
        return *activeItem;
    }

    ItemType NoteManager::get_type()
    {
        INFO("this ptr: %p, item ptr: %p", this, activeItem);
        if (!activeItem)
            return ItemType::invalid;
        return activeItem->get_type();
    }

    Transform* NoteManager::get_leftArrow()
    {
        GetNameInPrefab(get_leftArrowName());
    }

    Transform* NoteManager::get_rightArrow()
    {
        GetNameInPrefab(get_rightArrowName());
    }

    Transform* NoteManager::get_leftDot()
    {
        GetNameInPrefab(get_leftDotName());
    }

    Transform* NoteManager::get_rightDot()
    {
        GetNameInPrefab(get_rightDotName());
    }

    Transform* NoteManager::get_leftDebris()
    {
        GetNameInPrefab(get_leftDebrisName());
    }

    Transform* NoteManager::get_rightDebris()
    {
        GetNameInPrefab(get_rightDebrisName());
    }

    Transform* NoteManager::get_bomb()
    {
        GetNameInPrefab(get_bombName());
    }

    Il2CppString* NoteManager::get_leftArrowName()
    {
        if (!leftArrowName)
            leftArrowName = il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("LeftArrow");
        return leftArrowName;
    }

    Il2CppString* NoteManager::get_rightArrowName()
    {
        if (!rightArrowName)
            rightArrowName = il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("RightArrow");
        return rightArrowName;
    }

    Il2CppString* NoteManager::get_leftDotName()
    {
        if (!leftDotName)
            leftDotName = il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("LeftDot");
        return leftDotName;
    }

    Il2CppString* NoteManager::get_rightDotName()
    {
        if (!rightDotName)
            rightDotName = il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("RightDot");
        return rightDotName;
    }

    Il2CppString* NoteManager::get_leftDebrisName()
    {
        if (!leftDebrisName)
            leftDebrisName = il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("LeftDebris");
        return leftDebrisName;
    }

    Il2CppString* NoteManager::get_rightDebrisName()
    {
        if (!rightDebrisName)
            rightDebrisName = il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("RightDebris");
        return rightDebrisName;
    }

    Il2CppString* NoteManager::get_bombName()
    {
        if (!bombName)
            bombName = il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("Bomb");
        return bombName;
    }

}
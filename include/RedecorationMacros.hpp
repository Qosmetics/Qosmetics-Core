#pragma once
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/Transform.hpp"

#define MAKE_CLONE_AND_PARENT(identifier)                                                               \
    static UnityEngine::GameObject* parent_clone_##identifier = nullptr;                                \
    if (parent_clone_##identifier)                                                                      \
    {                                                                                                   \
        UnityEngine::Object::DestroyImmediate(parent_clone_##identifier);                               \
    }                                                                                                   \
    static ConstString parent_name_##identifier("parent_clone_" #identifier);                           \
    parent_clone_##identifier = UnityEngine::GameObject::New_ctor(parent_name_##identifier);            \
    parent_clone_##identifier->SetActive(false);                                                        \
    UnityEngine::Object::DontDestroyOnLoad(parent_clone_##identifier);                                  \
    UnityEngine::Object::Instantiate(identifier, parent_clone_##identifier->get_transform());           \
    auto type_##identifier = il2cpp_utils::GetSystemType(il2cpp_utils::ExtractType(identifier->klass)); \
    auto clone_##identifier = parent_clone_##identifier->GetComponentsInChildren(type_##identifier)[0]; \
    clone_##identifier->get_gameObject()->set_name(identifier->get_name());                             \
    reinterpret_cast<UnityEngine::Component*&>(self->identifier) = clone_##identifier;                  \
    self->identifier->get_gameObject()->SetActive(true)

#define DESTROY_CLONE_PARENT(identifier) \
    UnityEngine::Object::Destroy(parent_clone_##identifier);

#define REDECORATE(identifier) \
    Qosmetics::Core::Redecoration::Redecorate(reinterpret_cast<Il2CppObject*&>(self->identifier), #identifier, type_##identifier, self_type, container)

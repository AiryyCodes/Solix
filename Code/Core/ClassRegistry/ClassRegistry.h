#pragma once

#include "Core/ClassRegistry/Property.h"
#include "Core/Logger.h"

#include <string>
#include <vector>

class Object;

using RegisterPropertiesFunc = void (*)();

class ClassRegistry
{
public:
    static void RegisterClass(
        const std::string &name,
        const std::string &base,
        std::function<Object *()> factory,
        RegisterPropertiesFunc registerPropsFunc);

    static ClassInfo *GetClass(const std::string &name)
    {
        auto it = m_Classes.find(name);
        if (it != m_Classes.end())
            return &it->second;
        return nullptr;
    }

    static void RegisterProperty(const std::string &class_name, const Property &prop)
    {
        auto *cls = GetClass(class_name);
        if (cls)
        {
            // Check if property already registered by name
            auto it = std::find_if(cls->properties.begin(), cls->properties.end(),
                                   [&prop](const Property &p)
                                   { return p.name == prop.name; });
            if (it == cls->properties.end())
            {
                cls->properties.push_back(prop);
            }
            else
            {
                LOG_WARNING("Property '{}' already registered for class '{}', skipping duplicate.", prop.name, class_name);
            }
        }
    }

    static void SetCurrentPropertyGroup(const std::string &group)
    {
        m_CurrentGroup = group;
    }

    static std::string GetCurrentPropertyGroup()
    {
        return m_CurrentGroup;
    }

private:
    static inline std::unordered_map<std::string, ClassInfo> m_Classes;

    static inline std::string m_CurrentGroup = "";
};

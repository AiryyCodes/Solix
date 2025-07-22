#pragma once

#include "Core/ClassDB/Property.h"
#include "Core/Logger.h"

#include <string>
#include <vector>

class Object;

class ClassDB
{
public:
    static void RegisterClass(const std::string &name, const std::string &base, std::function<Object *()> factory);

    static ClassInfo *GetClass(const std::string &name)
    {
        auto it = classes.find(name);
        if (it != classes.end())
            return &it->second;
        return nullptr;
    }

    static void RegisterProperty(const std::string &class_name, const Property &prop)
    {
        auto *cls = GetClass(class_name);
        if (cls)
            cls->properties.push_back(prop);
    }

private:
    static inline std::unordered_map<std::string, ClassInfo> classes;
};

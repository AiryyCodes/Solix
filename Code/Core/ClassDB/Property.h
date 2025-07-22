#pragma once

#include "Core/Variant.h"

#include <string>
#include <functional>

class Object;

struct Property
{
    std::string name;
    std::function<Variant(Object *)> getter;
    std::function<void(Object *, const Variant &)> setter;
};

struct ClassInfo
{
    std::string name;
    std::string base;
    std::function<Object *()> factory;
    std::vector<Property> properties;
};

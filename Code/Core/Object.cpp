#include "Core/Object.h"
#include "Core/Variant.h"

#include <string>

Variant Object::GetProperty(const std::string &name) const
{
    const ClassInfo *info = ClassDB::GetClass(GetClassName());
    if (!info)
        return Variant();

    for (const auto &prop : info->properties)
    {
        if (prop.name == name)
            return prop.getter(const_cast<Object *>(this));
    }
    return Variant();
}

void Object::SetProperty(const std::string &name, const Variant &value)
{
    const ClassInfo *info = ClassDB::GetClass(GetClassName());
    if (!info)
        return;

    for (const auto &prop : info->properties)
    {
        if (prop.name == name)
        {
            prop.setter(const_cast<Object *>(this), value);
            return;
        }
    }
}

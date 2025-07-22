#pragma once

#include "Core/ClassDB/ClassDB.h"
#include "Core/Variant.h"

#include <string>

#define REGISTER_CLASS(CLASS, BASE) \
    ClassDB::RegisterClass(#CLASS, #BASE, []() -> Object * { return new CLASS("default"); })

#define REGISTER_PROPERTY(CLASS, NAME, GETTER, SETTER)                                                                                  \
    ClassDB::RegisterProperty(GetClassName(), Property{NAME,                                                                            \
                                                       [](Object *o) -> Variant { return Variant(static_cast<CLASS *>(o)->GETTER()); }, \
                                                       [](Object *o, const Variant &v) { static_cast<CLASS *>(o)->SETTER(v); }});

class Object
{
public:
    virtual ~Object() = default;

    virtual const char *GetClassName() const = 0;
    virtual void OnRegisterProperties() {}

    virtual Variant GetProperty(const std::string &name) const;
    virtual void SetProperty(const std::string &name, const Variant &value);
};

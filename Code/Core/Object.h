#pragma once

#include "Core/ClassRegistry/ClassRegistry.h"
#include "Core/Variant.h"

#include <string>

#define REGISTER_CLASS(CLASS, BASE)                        \
    ClassRegistry::RegisterClass(                          \
        #CLASS,                                            \
        #BASE,                                             \
        []() -> Object * { return new CLASS("default"); }, \
        &CLASS::OnRegisterProperties)

#define REGISTER_PROPERTY(CLASS, NAME, GETTER, SETTER)                                                                                \
    ClassRegistry::RegisterProperty(#CLASS, Property{NAME,                                                                            \
                                                     [](Object *o) -> Variant { return Variant(static_cast<CLASS *>(o)->GETTER()); }, \
                                                     [](Object *o, const Variant &v) { static_cast<CLASS *>(o)->SETTER(v); },         \
                                                     ClassRegistry::GetCurrentPropertyGroup()});

#define REGISTER_PROPERTY_GROUP(GROUP_NAME) \
    ClassRegistry::SetCurrentPropertyGroup(GROUP_NAME)

class Object
{
public:
    virtual ~Object() = default;

    virtual const char *GetClassName() const = 0;

    virtual Variant GetProperty(const std::string &name) const;
    virtual void SetProperty(const std::string &name, const Variant &value);
};

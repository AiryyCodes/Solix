#include "ClassRegistry.h"
#include "Core/Object.h"

void ClassRegistry::RegisterClass(
    const std::string &name,
    const std::string &base,
    std::function<Object *()> factory,
    RegisterPropertiesFunc registerPropsFunc)
{
    ClassInfo &info = m_Classes[name];
    info.name = name;
    info.base = base;
    info.factory = factory;

    if (!info.propertiesRegistered && registerPropsFunc)
    {
        registerPropsFunc();
        info.propertiesRegistered = true;
    }
}

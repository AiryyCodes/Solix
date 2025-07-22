#include "ClassDB.h"
#include "Core/Object.h"

void ClassDB::RegisterClass(const std::string &name, const std::string &base, std::function<Object *()> factory)
{
    LOG_INFO("Registering class: {}", name);

    ClassInfo info;
    info.name = name;
    info.base = base;
    info.factory = factory;
    classes[name] = info;

    Object *instance = factory();
    if (instance)
    {
        instance->OnRegisterProperties();
        delete instance;
    }
}

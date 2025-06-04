#pragma once

#include <string>

struct AssertData
{
    std::string message;
    int line;
    const char *file;
};

void custom_assert(bool condition, const AssertData &data);

#ifdef TARGET_DEBUG
#define ASSERT(condition, message) custom_assert(condition, AssertData{message, __LINE__, __FILE__});
#else
#define ASSERT(condition, message) ((void)0)
#endif

#define STATIC_ASSERT(condition, message) static_assert(static_cast<bool>(condition), message)

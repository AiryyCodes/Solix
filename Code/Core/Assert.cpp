#include "Core/Assert.h"
#include "Core/Logger.h"

void custom_assert(bool condition, const AssertData &data)
{
    if (condition)
        return;

    LOG_ERROR("Assertion failed in file: '{}' at line: {}: {}", data.file, data.line, data.message);
    abort();
}

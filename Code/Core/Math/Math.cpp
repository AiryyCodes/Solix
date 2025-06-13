#include "Core/Math/Math.h"

#include <algorithm>

float Math::ToRadians(float degrees)
{
    return degrees * (PI / 180.0f);
}

float Math::Clamp(float value, float min, float max)
{
    return std::clamp(value, min, max);
}

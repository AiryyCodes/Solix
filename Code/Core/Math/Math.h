#pragma once

#define PI 3.14159265358979323846

class Math
{
public:
    static float ToRadians(float degrees);

    static float Clamp(float value, float min, float max);
};

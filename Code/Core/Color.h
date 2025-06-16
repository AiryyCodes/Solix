#pragma once

struct Color
{
    float r;
    float g;
    float b;
    float a;

    Color()
        : r(0.0f), g(0.0f), b(0.0f), a(255.0f) {}
    Color(float r, float g, float b, float a)
        : r(r), g(g), b(b), a(a) {}

    Color Normalize() const;
};

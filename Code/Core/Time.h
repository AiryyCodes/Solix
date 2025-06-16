#pragma once

#include <chrono>
class Time
{
public:
    static void Update();

    static float GetDelta() { return m_Delta; }

    static double GetNow();

private:
    static float m_Delta;
    static double m_LastTime;
};

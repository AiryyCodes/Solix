#include "Core/Time.h"
#include <chrono>

float Time::m_Delta;
double Time::m_LastTime = GetNow();

void Time::Update()
{
    double now = GetNow();
    m_Delta = static_cast<float>(now - m_LastTime);
    m_LastTime = now;
}

double Time::GetNow()
{
    auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
    return std::chrono::duration<double>(now).count();
}

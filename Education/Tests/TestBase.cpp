#include "TestBase.h"

#include <chrono>

void TestBase::StartTimer()
{
    StartTime = std::chrono::steady_clock::now();
}

double TestBase::StopAndReturnElapsedTime() const
{
    const auto EndTime = std::chrono::steady_clock::now();
    const auto ElapsedTime = EndTime - StartTime;
    return std::chrono::duration_cast<std::chrono::duration<double>>(ElapsedTime).count();
}

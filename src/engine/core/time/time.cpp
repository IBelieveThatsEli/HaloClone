#include "time.hpp"

using namespace Core;

Time::Time() noexcept
    :   m_lastTime(clock::now()),
        m_deltaSeconds(0.0),
        m_totalSeconds(0.0)
{}

void Time::Tick() noexcept
{
    const time_point now = clock::now();
    const std::chrono::duration<double> delta = now - m_lastTime;

    m_deltaSeconds = delta.count();
    m_totalSeconds += m_deltaSeconds;
    m_lastTime = now;
}

f64 Time::GetDeltaSeconds() const noexcept 
{
    return m_deltaSeconds;
}

f64 Time::GetTotalSeconds() const noexcept
{
    return m_totalSeconds;
}

void Time::Reset() noexcept
{
    m_lastTime = clock::now();
    m_deltaSeconds = 0.0;
    m_totalSeconds = 0.0;
}
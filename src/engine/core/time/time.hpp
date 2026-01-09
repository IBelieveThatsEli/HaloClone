#pragma once

#include "core/utils/types.hpp"

#include <chrono>

namespace Core
{
    class Time final 
    {
        public:
            using clock = std::chrono::steady_clock;
            using time_point = clock::time_point;

            Time() noexcept;
            
            void Tick() noexcept;

            f64 GetDeltaSeconds() const noexcept;

            f64 GetTotalSeconds() const noexcept;

            void Reset() noexcept;

        private:
            time_point m_lastTime;
            f64 m_deltaSeconds;
            f64 m_totalSeconds;
    };
} // Core
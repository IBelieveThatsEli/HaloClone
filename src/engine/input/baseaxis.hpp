#pragma once

#include <initializer_list>
#include <unordered_map>
#include <cmath>

#include "core/utils/types.hpp"

namespace Input
{
    template <typename T>
    class BaseAxis
    {
        public:
            BaseAxis(std::initializer_list<T> axes)
            {
                for (auto axis : axes)
                {
                    m_raw[axis]      = 0.0f;
                    m_current[axis]  = 0.0f;
                    m_previous[axis] = 0.0f;
                }
            }

            void SetSmoothingEnabled(bool enabled) { m_smoothingEnabled = enabled; }
            void SetSmoothingSpeed(f32 speed) { m_smoothingSpeed = speed; }

            void UpdateAxisRaw(T axis, f32 rawValue)
            {
                if (m_raw.find(axis) == m_raw.end()) return;
                m_raw[axis] = rawValue;
            }

            void Update(f32 dt)
            {
                for (auto& [axis, rawValue] : m_raw)
                {
                    m_previous[axis] = m_current[axis];

                    if (m_smoothingEnabled)
                    {
                        f32 a = 1.0f - std::exp(-m_smoothingSpeed * dt);
                        m_current[axis] = m_current[axis] + (rawValue - m_current[axis]) * a;
                    }
                    else
                    {
                        m_current[axis] = rawValue;
                    }
                }
            }

            float GetAxis(T axis) const noexcept
            {
                auto it = m_current.find(axis);
                if (it == m_current.end())
                    return 0.0f;
                return it->second;
            }

            f32 GetAxisDelta(T axis) const noexcept
            {
                if (m_current.find(axis) == m_current.end()) return 0.0f;
                return m_current.at(axis) - m_previous.at(axis);
            }

        private:
            std::unordered_map<T, f32> m_raw;
            std::unordered_map<T, f32> m_current;
            std::unordered_map<T, f32> m_previous;

            bool  m_smoothingEnabled = false;
            f32   m_smoothingSpeed   = 12.0f; // higher = faster response
    };
} // Input

#pragma once

#include <initializer_list>
#include <unordered_map>

#include "types/action.hpp"
#include "types/mod.hpp"

namespace Input
{
    template <typename T>
    class BaseButton
    {
        public:
            BaseButton(std::initializer_list<T> buttons)
            {
                for (auto button : buttons)
                {
                    m_currentState [button] = false;
                    m_previousState[button] = false;
                }
            }
            ~BaseButton() = default;

            void OnButtonEvent(T button, i32 scancode, Action action, Mod mods)
            {
                if (m_currentState.find(button) == m_currentState.end())
                    return;

                //m_previousState[button] = m_currentState[button];

                if (action == Action::Press)
                    m_currentState[button] = true;
                else if (action == Action::Release)
                    m_currentState[button] = false;
            }

            void Update()
            {
                for (auto& [button, state] : m_currentState)
                    m_previousState[button] = state;
            }

            void SetButtonState(T button, bool pressed)
            {
                m_currentState.at(button) = pressed;
            }

            [[nodiscard]] bool IsButtonDown(T button) const
            {
                return m_currentState.at(button) && !m_previousState.at(button);
            }

            [[nodiscard]] bool IsButtonUp(T button) const
            {
                return !m_currentState.at(button) && m_previousState.at(button);
            }

            [[nodiscard]] bool IsButtonHeld(T button) const
            {
                return m_currentState.at(button);
            }

            [[nodiscard]] bool IsButtonReleased(T button) const
            {
                return !m_currentState.at(button);
            }

        private:
            std::unordered_map<T, bool> m_currentState  = {};
            std::unordered_map<T, bool> m_previousState = {};
    };
} // Input

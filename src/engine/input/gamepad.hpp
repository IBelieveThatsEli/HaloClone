#pragma once

#include "basebutton.hpp"
#include "baseaxis.hpp"
#include "input/types/action.hpp"
#include "types/gamepadbutton.hpp"
#include "types/gamepadaxis.hpp"

namespace Input
{
    class Gamepad final
    {
        public:
            BaseButton<GamepadButton> buttons;
            BaseAxis<GamepadAxis>     axes;

            Gamepad(i32 id) 
                : m_id(id),
                  buttons({
                            GamepadButton::A, GamepadButton::B, GamepadButton::X, GamepadButton::Y,
                            GamepadButton::LeftBumper, GamepadButton::RightBumper,
                            GamepadButton::Back, GamepadButton::Start, GamepadButton::Guide,
                            GamepadButton::LeftStick, GamepadButton::RightStick,
                            GamepadButton::DPadUp, GamepadButton::DPadRight, GamepadButton::DPadDown, GamepadButton::DPadLeft,
                            GamepadButton::Misc1, GamepadButton::Paddle1, GamepadButton::Paddle2, GamepadButton::Paddle3, GamepadButton::Paddle4,
                          }),
                  axes({
                           GamepadAxis::LeftStickX,GamepadAxis::LeftStickY,
                           GamepadAxis::RightStickX,GamepadAxis::RightStickY,
                           GamepadAxis::LeftTrigger,GamepadAxis::RightTrigger,
                          })
            {}

            void Update(f32 dt)
            {
                buttons.Update();
                axes.Update(dt);
            }

            [[nodiscard]] i32 GetID() const noexcept { return m_id; }
    
            void ButtonListener(GamepadButton button, Action action)
            {
                buttons.SetButtonState(button, action == Action::Press); 
            }

            void AxisListener(GamepadAxis axis, f32 rawValue)
            {
                axes.UpdateAxisRaw(axis, rawValue);
            }

        private:
            i32 m_id;
    };
} // Input

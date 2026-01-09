// TODO shouldnt be here..

#pragma once

#include "core/utils/types.hpp"

#include "input/types/gamepadaxis.hpp"
#include "input/types/gamepadbutton.hpp"
#include "input/types/gamepadconnection.hpp"
#include "input/types/key.hpp"
#include "input/types/action.hpp"
#include "input/types/mousebutton.hpp"
#include "input/types/mod.hpp"

#include <functional>

namespace Runtime 
{
    class EventBus final
    {
        public:
            static EventBus& GetInstance();

            template <typename ...Args>
            using Callback = std::function<void(Args...)>; 

            void AddFramebufferListener(Callback<i32, i32>&& func);
            void AddKeyListener(Callback<Input::Key, i32, Input::Action, Input::Mod>&& func);
            void AddCursorPosListener(Callback<f64, f64>&& func);
            void AddCursorEnterListener(Callback<bool>&& func);
            void AddMouseButtonListener(Callback<Input::MouseButton, Input::Action, Input::Mod>&& func);
            void AddScrollbackListener(Callback<f64, f64>&& func);
            void AddWindowCloseListener(Callback<>&& func);
            void AddWindowFocusListener(Callback<bool>&& func);
            void AddGamepadConnectionListener(Callback<i32, Input::GamepadConnection>&& func);
            void AddGamepadButtonListener(Callback<Input::GamepadButton, Input::Action>&& func);
            void AddGamepadAxisListener(Callback<Input::GamepadAxis, f32>&& func);

            void DispatchFramebufferListener(i32, i32);
            void DispatchKeyListener(Input::Key, i32, Input::Action, Input::Mod);
            void DispatchCursorPosListener(f64, f64);
            void DispatchCursorEnterListener(bool);
            void DispatchMouseButtonListener(Input::MouseButton, Input::Action, Input::Mod);
            void DispatchScrollbackListener(f64, f64);
            void DispatchWindowCloseListener();
            void DispatchWindowFocusListener(bool);
            void DispatchGamepadConnectionListener(i32, Input::GamepadConnection);
            void DispatchGamepadButtonListener(Input::GamepadButton, Input::Action);
            void DispatchGamepadAxisListener(Input::GamepadAxis, f32);

        private:
            std::vector<Callback<i32, i32>> m_frameListeners {};
            std::vector<Callback<Input::Key, i32, Input::Action, Input::Mod>> m_keyListeners {};
            std::vector<Callback<f64, f64>> m_cursorPosListeners {};
            std::vector<Callback<bool>> m_cursorEnterListeners {};
            std::vector<Callback<Input::MouseButton, Input::Action, Input::Mod>> m_mouseButtonListeners {};
            std::vector<Callback<f64, f64>> m_scrollListeners {};
            std::vector<Callback<>> m_windowCloseListeners {};
            std::vector<Callback<bool>> m_windowFocusListeners {};
            std::vector<Callback<i32, Input::GamepadConnection>> m_gamepadConnectionListeners {};
            std::vector<Callback<Input::GamepadButton, Input::Action>> m_gamepadButtonListeners {};
            std::vector<Callback<Input::GamepadAxis, f32>> m_gamepadAxisListeners {};
    };
} // Runtime 

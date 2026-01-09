#pragma once

#include <memory>

#include "keyboard.hpp"
#include "mouse.hpp"
#include "gamepad.hpp"
#include "core/utils/types.hpp"

namespace Input
{
    class Manager final
    {
        public:
            Manager();
            ~Manager();

            void Update(f32 dt);
            
            [[nodiscard]] Keyboard* GetKeyboard() const noexcept { return m_keyboard.get(); }
            [[nodiscard]] Mouse*    GetMouse   () const noexcept { return m_mouse.get();    }
            [[nodiscard]] Gamepad*  GetGamepad () const noexcept { return m_gamepad.get();  }

            void OnGamepadConnected   (i32 jid);
            void OnGamepadDisconnected(i32 jid);

            void EnableGamepad (std::unique_ptr<Gamepad> gamepad);
            void EnableKeyboard(std::unique_ptr<Keyboard> keyboard);
            void EnableMouse   (std::unique_ptr<Mouse> mouse);
            
            void DisableGamepad();
            void DisableKeyboard();
            void DisableMouse();
        private:
            std::unique_ptr<Keyboard>   m_keyboard  {nullptr};
            std::unique_ptr<Mouse>      m_mouse     {nullptr};
            std::unique_ptr<Gamepad>    m_gamepad   {nullptr};
    };
} // Input

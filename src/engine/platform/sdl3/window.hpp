#pragma once

#include "core/window/basewindow.hpp"
#include "utils/types.hpp"

#include <string_view>

struct SDL_Window;

namespace SDL3
{
    class Window : public Core::BaseWindow
    {
        public:
            Window(Properties& properties);
            ~Window() override;

            bool IsOpen() const override;
            void Close () override;

            void PollEvents() override;
            void SwapBuffers() override;

            void SetWidth (i32 width) override;
            void SetHeight(i32 height) override;
            void SetTitle (std::string_view title) override;

            [[nodiscard]] SDL_Window* GetHandle() noexcept { return m_handle; }

            void SetResizable     (bool flag) override;
            void SetVisible       (bool flag) override;
            void SetFocused       (bool flag) override;
            void SetIconified     (bool flag) override;
            void SetFloating      (bool flag) override;
            void SetScaleToMonitor(bool flag) override;
            void SetTransparent   (bool flag) override;
            void SetVSync         (bool flag) override;
            void SetWindowMode    (Mode mode) override;

        private:
            SDL_Window* m_handle {nullptr};
    };
} // SDL3

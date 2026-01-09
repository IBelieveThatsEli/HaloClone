#pragma once

#include <string_view>

#include "core/utils/types.hpp"
#include "platform/basewindow/basewindow.hpp"

struct GLFWwindow;

namespace GLFW
{
    class Window final : public Platform::BaseWindow
    {
        public:
            Window(const Properties& propeties);
            ~Window() override;

            bool IsOpen() const override;
            void Close () override;

            void PollEvents() override;
            void SwapBuffers() override;

            void SetWidth (i32 width) override;
            void SetHeight(i32 height) override;
            void SetTitle (std::string_view title) override;

            void ChangeGraphicsAPI(const Core::GraphicsAPI& api) override;

            void* GetHandle() noexcept override { return m_handle; }

            void SetResizable     (bool flag) override;
            void SetVisible       (bool flag) override;
            void SetFocused       (bool flag) override;
            void SetIconified     (bool flag) override;
            void SetFloating      (bool flag) override;
            void SetScaleToMonitor(bool flag) override;
            void SetTransparent   (bool flag) override;
            void SetVSync         (bool flag) override;
            void SetWindowMode    (Mode mode) override;

            bool InitGLAD() noexcept override;
            bool CreateVKWindowSurface() noexcept override;
    
        protected:
            void CreateWindow() override;
            void DestroyWindow() override;

        private:
            GLFWwindow* m_handle { nullptr };

            void CenterWindow();
    };
} // GLFW

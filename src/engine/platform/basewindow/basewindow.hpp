#pragma once

#include "utils/types.hpp"
#include "core/api/api.hpp"

#include <string_view>
#include <vector>
#include <functional>

namespace Core 
{
    class BaseWindow
    {
        public:
            enum class Mode : u8
            {
                Windowed, 
                BorderlessWindow, 
                Fullscreen, 
                FullscreenBorderless
            };

            struct Properties 
            {
                i32              width      { 800 };
                i32              height     { 600 };
                i32              prevWidth  { width };
                i32              prevHeight { height };
                std::string_view title      { "Window" };

                Mode mode      { Mode::Windowed };
                
                bool resizable { true };
                bool visible   { true };
                bool focused   { true };
                bool floating  { true };
                bool vsync     { true };

                bool iconify         { false };
                bool scaleToMonitor  { false };
                bool transparent     { false };

                GraphicsAPI graphicsAPI { GraphicsAPI::OpenGL };

                i32 glMajorVersion  { 4 };
                i32 glMinorVersion  { 0 };
            };

        public:
            explicit BaseWindow(const Properties& properties);

            virtual ~BaseWindow() = default;

            virtual bool IsOpen() const = 0;
            virtual void Close () = 0;

            virtual void PollEvents() = 0;
            virtual void SwapBuffers() = 0;

            virtual void SetWidth (i32 width) = 0;
            virtual void SetHeight(i32 height) = 0;
            virtual void SetTitle (std::string_view title) = 0;

            virtual void ChangeGraphicsAPI(const Core::GraphicsAPI& api) = 0;

            [[nodiscard]] i32                 GetWidth () const noexcept { return m_properties.width;  }
            [[nodiscard]] i32                 GetHeight() const noexcept { return m_properties.height; }
            [[nodiscard]] std::string_view    GetTitle () const noexcept { return m_properties.title;  }

            virtual void SetResizable     (bool flag) = 0;
            virtual void SetVisible       (bool flag) = 0;
            virtual void SetFocused       (bool flag) = 0;
            virtual void SetIconified     (bool flag) = 0;
            virtual void SetFloating      (bool flag) = 0;
            virtual void SetScaleToMonitor(bool flag) = 0;
            virtual void SetTransparent   (bool flag) = 0;
            virtual void SetVSync         (bool flag) = 0;
            virtual void SetWindowMode    (Mode mode) = 0;

            [[nodiscard]] bool IsResizable      () const { return m_properties.resizable;        }
            [[nodiscard]] bool IsVisible        () const { return m_properties.visible;          }
            [[nodiscard]] bool IsFocused        () const { return m_properties.focused;          }
            [[nodiscard]] bool IsIconified      () const { return m_properties.iconify;          }
            [[nodiscard]] bool IsFloating       () const { return m_properties.floating;         }
            [[nodiscard]] bool IsScaledToMonitor() const { return m_properties.scaleToMonitor;   }
            [[nodiscard]] bool IsTransparent    () const { return m_properties.transparent;      }
            [[nodiscard]] bool IsVSyncEnable    () const { return m_properties.vsync;            }

            [[nodiscard]] const Properties& GetProperties() const noexcept { return m_properties; }

            void AddFramebufferCallback(std::function<void(i32, i32)>&& func);
            void AddCloseCallback      (std::function<void(        )>&& func);
            void AddFocusCallback      (std::function<void(bool    )>&& func);

            [[nodiscard]] std::vector<std::function<void(i32, i32)>>& GetFramebufferCallbacks() noexcept { return m_framebufferCallbacks; }
            [[nodiscard]] std::vector<std::function<void(        )>>& GetCloseCallbacks      () noexcept { return m_closeCallbacks;       }
            [[nodiscard]] std::vector<std::function<void(bool    )>>& GetFocusCallbacks      () noexcept { return m_focusCallbacks;       }

            [[nodiscard]] virtual bool InitGLAD() noexcept = 0;
            [[nodiscard]] virtual bool CreateVKWindowSurface() noexcept = 0;

        protected:
            virtual void CreateWindow() = 0;
            virtual void DestroyWindow() = 0;

            Properties m_properties {};
            bool m_isOpen { true };

            std::vector<std::function<void(i32, i32)>> m_framebufferCallbacks {
                {[&](i32 w, i32 h) { m_properties.width = w; m_properties.height = h; }}
            };
            std::vector<std::function<void()>>         m_closeCallbacks       {
                [&]() { m_isOpen = false; }
            };
            std::vector<std::function<void(bool)>>     m_focusCallbacks       {
                {[&](bool focused) { m_properties.focused = focused; }}
            };
    };
} // Core 

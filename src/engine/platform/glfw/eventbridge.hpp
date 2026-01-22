#pragma once

#include "core/utils/types.hpp"

#include "platform/ieventbridge/ieventbridge.hpp"

struct GLFWwindow;

namespace GLFW
{
    // class EventBridge final
    // {
    //     public:
    //         static void SetupCallbacks(GLFWwindow*);
    //         static void UpdateGamepads();

    //     private:
    //         static void FramebufferSizeCallback(GLFWwindow*, i32, i32);
    //         static void KeyCallback            (GLFWwindow*, i32, i32, i32, i32);
    //         static void CursorPosCallback      (GLFWwindow*, f64, f64);
    //         static void CursorEnterCallback    (GLFWwindow*, i32);
    //         static void MouseButtonCallback    (GLFWwindow*, i32, i32, i32);
    //         static void ScrollCallback         (GLFWwindow*, f64, f64);
    //         static void WindowCloseCallback    (GLFWwindow*);
    //         static void WindowFocusCallback    (GLFWwindow*, i32);
    //         static void GamepadCallback        (i32, i32);
    // };
    class EventBridge final : public Platform::IEventBridge
    {
        public:
            EventBridge() = default;

            void Init(void* windowHandle) override;

            void PollEvents() override;
        
        private:
            void FramebufferSizeCallback(GLFWwindow*, i32, i32);
            void KeyCallback(GLFWwindow*, i32, i32, i32, i32);
            void CursorPosCallback(GLFWwindow*, f64, f64);
            void CursorEnterCallback(GLFWwindow*, i32);
            void MouseButtonCallback(GLFWwindow*, i32, i32, i32);
            void ScrollCallback(GLFWwindow*, f64, f64);
            void WindowCloseCallback(GLFWwindow*);
            void WindowFocusCallback(GLFWwindow*, i32);
            // void GamepadCallback(i32, i32);
            void UpdateGamepads();
    };
} // GLFW

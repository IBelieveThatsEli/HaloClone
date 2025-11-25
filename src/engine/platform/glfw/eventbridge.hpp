#pragma once

#include "utils/types.hpp"

struct GLFWwindow;

namespace GLFW
{
    class EventBridge
    {
        public:
            static void SetupCallbacks(GLFWwindow*);
            static void UpdateGamepads         ();

        private:
            static void FramebufferSizeCallback(GLFWwindow*, i32, i32);
            static void KeyCallback            (GLFWwindow*, i32, i32, i32, i32);
            static void CursorPosCallback      (GLFWwindow*, f64, f64);
            static void CursorEnterCallback    (GLFWwindow*, i32);
            static void MouseButtonCallback    (GLFWwindow*, i32, i32, i32);
            static void ScrollCallback         (GLFWwindow*, f64, f64);
            static void WindowCloseCallback    (GLFWwindow*);
            static void WindowFocusCallback    (GLFWwindow*, i32);
            static void GamepadCallback        (i32, i32);
    };
} // GLFW

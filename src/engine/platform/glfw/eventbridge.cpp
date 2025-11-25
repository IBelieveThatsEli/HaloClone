#include "eventbridge.hpp"

#include <GLFW/glfw3.h>

#include "core/events/eventbus.hpp"
#include "input/types/action.hpp"
#include "input/types/gamepadbutton.hpp"
#include "input/types/gamepadconnection.hpp"
#include "input/types/mousebutton.hpp"
#include "input/types/key.hpp"
#include "input/types/mod.hpp"

using namespace GLFW;
using namespace Core;
using namespace Input;

static Key ConvertGLFWKey(i32 glfwKey)
{
    if (glfwKey < static_cast<int>(Key::Unknown) || glfwKey > static_cast<int>(Key::Menu))
        return Key::Unknown;
    return static_cast<Key>(glfwKey);
}
static Action ConvertGLFWAction(i32 glfwAction)
{
    switch (glfwAction)
    {
        case GLFW_PRESS:   
            return Action::Press;
        case GLFW_RELEASE: 
            return Action::Release;
        case GLFW_REPEAT:  
            return Action::Repeat;
        default:           
            return Action::Release;
    }
}
static Mod operator|(Mod a, Mod b) {
    return static_cast<Mod>(
        static_cast<int32_t>(a) | static_cast<int32_t>(b)
    );
}
static Mod& operator|=(Mod& a, Mod b) {
    a = a | b;
    return a;
}
static bool operator&(Mod a, Mod b) {
    return (static_cast<int32_t>(a) & static_cast<int32_t>(b)) != 0;
}
static Mod ConvertGLFWMod(i32 glfwMod)
{
    Mod mod = Mod::None;

    if (glfwMod & GLFW_MOD_SHIFT)     mod |= Mod::Shift;
    if (glfwMod & GLFW_MOD_CONTROL)   mod |= Mod::Control;
    if (glfwMod & GLFW_MOD_ALT)       mod |= Mod::Alt;
    if (glfwMod & GLFW_MOD_SUPER)     mod |= Mod::Super;
    if (glfwMod & GLFW_MOD_CAPS_LOCK) mod |= Mod::CapsLock;
    if (glfwMod & GLFW_MOD_NUM_LOCK)  mod |= Mod::NumLock;

    return mod;
}
static MouseButton ConvertGLFWMouseButton(i32 glfwMouseButton)
{
    if (glfwMouseButton < 0 || glfwMouseButton > 7)
    {
        return MouseButton::_1;
    }

    return static_cast<MouseButton>(glfwMouseButton);
}
static GamepadConnection ConvertGLFWGamepadConnection(i32 event)
{
    if (event == GLFW_CONNECTED)
        return GamepadConnection::Connected;

    return GamepadConnection::Disconnected;
}
static GamepadButton ConvertGLFWGamepadButton(i32 button)
{
    switch (button)
    {
        case GLFW_GAMEPAD_BUTTON_A:             return GamepadButton::A;
        case GLFW_GAMEPAD_BUTTON_B:             return GamepadButton::B;
        case GLFW_GAMEPAD_BUTTON_X:             return GamepadButton::X;
        case GLFW_GAMEPAD_BUTTON_Y:             return GamepadButton::Y;

        case GLFW_GAMEPAD_BUTTON_LEFT_BUMPER:   return GamepadButton::LeftBumper;
        case GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER:  return GamepadButton::RightBumper;

        case GLFW_GAMEPAD_BUTTON_BACK:          return GamepadButton::Back;
        case GLFW_GAMEPAD_BUTTON_START:         return GamepadButton::Start;
        case GLFW_GAMEPAD_BUTTON_GUIDE:         return GamepadButton::Guide;

        case GLFW_GAMEPAD_BUTTON_LEFT_THUMB:    return GamepadButton::LeftStick;
        case GLFW_GAMEPAD_BUTTON_RIGHT_THUMB:   return GamepadButton::RightStick;

        case GLFW_GAMEPAD_BUTTON_DPAD_UP:       return GamepadButton::DPadUp;
        case GLFW_GAMEPAD_BUTTON_DPAD_RIGHT:    return GamepadButton::DPadRight;
        case GLFW_GAMEPAD_BUTTON_DPAD_DOWN:     return GamepadButton::DPadDown;
        case GLFW_GAMEPAD_BUTTON_DPAD_LEFT:     return GamepadButton::DPadLeft;

        default:                                return GamepadButton::COUNT;
    }
}
static GamepadAxis ConvertGLFWGamepadAxis(i32 axis)
{
    switch (axis)
    {
        case GLFW_GAMEPAD_AXIS_LEFT_X:         return GamepadAxis::LeftStickX;
        case GLFW_GAMEPAD_AXIS_LEFT_Y:         return GamepadAxis::LeftStickY;

        case GLFW_GAMEPAD_AXIS_RIGHT_X:        return GamepadAxis::RightStickX;
        case GLFW_GAMEPAD_AXIS_RIGHT_Y:        return GamepadAxis::RightStickY;

        case GLFW_GAMEPAD_AXIS_LEFT_TRIGGER:   return GamepadAxis::LeftTrigger;
        case GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER:  return GamepadAxis::RightTrigger;

        default:
            return GamepadAxis::COUNT; // invalid
    }
}

void EventBridge::SetupCallbacks(GLFWwindow* window)
{
    glfwSetFramebufferSizeCallback  (window, FramebufferSizeCallback  );
    glfwSetKeyCallback              (window, KeyCallback              );
    glfwSetCursorPosCallback        (window, CursorPosCallback        );
    glfwSetCursorEnterCallback      (window, CursorEnterCallback      );
    glfwSetMouseButtonCallback      (window, MouseButtonCallback      );
    glfwSetScrollCallback           (window, ScrollCallback           );
    glfwSetWindowCloseCallback      (window, WindowCloseCallback      );
    glfwSetWindowFocusCallback      (window, WindowFocusCallback      );
    glfwSetJoystickCallback         (GamepadCallback);


    for(i32 jid = 0; jid <= GLFW_JOYSTICK_LAST; ++jid)
    {
        if(glfwJoystickPresent(jid))
        {
            EventBus::GetInstance()
                .DispatchGamepadConnectionListener(jid, GamepadConnection::Connected);
        }
    }

}

void EventBridge::FramebufferSizeCallback(GLFWwindow* window, i32 width, i32 height)
{
    EventBus::GetInstance().DispatchFramebufferListener(width, height);
}
void EventBridge::KeyCallback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods)
{
    EventBus::GetInstance()
        .DispatchKeyListener(
            ConvertGLFWKey(key), 
            scancode, 
            ConvertGLFWAction(action), 
            ConvertGLFWMod(mods)
        ); 
}
void EventBridge::CursorPosCallback(GLFWwindow* window, f64 x, f64 y)
{
    EventBus::GetInstance()
        .DispatchCursorPosListener(x, y);
}
void EventBridge::CursorEnterCallback(GLFWwindow* window, i32 entered)
{
    EventBus::GetInstance()
        .DispatchCursorEnterListener(entered == GLFW_TRUE);
}
void EventBridge::MouseButtonCallback(
        GLFWwindow* window, 
        i32         mousebutton, 
        i32         action, 
        i32         mods)
{
    EventBus::GetInstance()
        .DispatchMouseButtonListener(
            ConvertGLFWMouseButton(mousebutton),
            ConvertGLFWAction(action),
            ConvertGLFWMod(mods)
        );
}
void EventBridge::ScrollCallback(GLFWwindow* window, f64 x, f64 y)
{
    EventBus::GetInstance()
        .DispatchScrollbackListener(x, y);
}
void EventBridge::WindowCloseCallback(GLFWwindow* window)
{
    EventBus::GetInstance()
        .DispatchWindowCloseListener();
}
void EventBridge::WindowFocusCallback(GLFWwindow* window, i32 focused)
{
    EventBus::GetInstance()
        .DispatchWindowFocusListener(focused == GLFW_TRUE);
}
void EventBridge::GamepadCallback(i32 jid, i32 event)
{
    EventBus::GetInstance()
        .DispatchGamepadConnectionListener(jid, event == GLFW_CONNECTED ? GamepadConnection::Connected : GamepadConnection::Disconnected);
}

void EventBridge::UpdateGamepads()
{
    for(i32 jid = GLFW_JOYSTICK_1; jid <= GLFW_JOYSTICK_LAST; ++jid)
    {
        if(!glfwJoystickIsGamepad(jid))
            continue;

        GLFWgamepadstate state;
        if(!glfwGetGamepadState(jid, &state))
            continue;

        static GLFWgamepadstate prev[16] = {};

        for(i32 i = 0; i < GLFW_GAMEPAD_BUTTON_LAST + 1; ++i)
        {
            if(state.buttons[i] == prev[jid].buttons[i])
                continue;

            GamepadButton button = ConvertGLFWGamepadButton(i);
            Action action = ConvertGLFWAction(state.buttons[i]);

            EventBus::GetInstance()
                .DispatchGamepadButtonListener(button, action);
        }

        for (int i = 0; i < GLFW_GAMEPAD_AXIS_LAST + 1; ++i)
        {
            f32 value = state.axes[i];

            GamepadAxis axis = ConvertGLFWGamepadAxis(i);
            EventBus::GetInstance()
                .DispatchGamepadAxisListener(axis, value); 
        }

        prev[jid] = state;
    }
}

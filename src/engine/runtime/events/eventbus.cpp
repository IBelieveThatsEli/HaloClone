#include "eventbus.hpp"

using namespace Runtime; 

EventBus& EventBus::GetInstance()
{
    static EventBus bus;
    return bus;
}

void EventBus::AddFramebufferListener(Callback<i32, i32>&& func)
{
    if(func) { m_frameListeners.emplace_back(func); }
}
void EventBus::AddKeyListener(Callback<Input::Key, i32, Input::Action, Input::Mod>&& func)
{
    if(func) { m_keyListeners.emplace_back(func); }
}
void EventBus::AddCursorPosListener(Callback<f64, f64>&& func)
{
    if(func) { m_cursorPosListeners.emplace_back(func); }
}

void EventBus::AddCursorEnterListener(Callback<bool>&& func)
{
    if(func) { m_cursorEnterListeners.emplace_back(func); }
}
void EventBus::AddMouseButtonListener(Callback<Input::MouseButton, Input::Action, Input::Mod>&& func)
{
    if(func) { m_mouseButtonListeners.emplace_back(func); }
}
void EventBus::AddScrollbackListener(Callback<f64, f64>&& func)
{
    if(func) { m_scrollListeners.emplace_back(func); }
}
void EventBus::AddWindowCloseListener(Callback<>&& func)
{
    if(func) { m_windowCloseListeners.emplace_back(func); }
}
void EventBus::AddWindowFocusListener(Callback<bool>&& func)
{
    if(func) { m_windowFocusListeners.emplace_back(func); }
}
void EventBus::AddGamepadConnectionListener(Callback<i32, Input::GamepadConnection>&& func)
{
    if(func) { m_gamepadConnectionListeners.emplace_back(func); }
}
void EventBus::AddGamepadButtonListener(Callback<Input::GamepadButton, Input::Action>&& func)
{
    if(func) { m_gamepadButtonListeners.emplace_back(func); }
}
void EventBus::AddGamepadAxisListener(Callback<Input::GamepadAxis, f32>&& func)
{
    if (func) { m_gamepadAxisListeners.emplace_back(func); }
}

void EventBus::DispatchFramebufferListener(i32 width, i32 height)
{
    for(auto& func : m_frameListeners) 
        func(width, height);
}
void EventBus::DispatchKeyListener(
        Input::Key      key, 
        i32             scancode, 
        Input::Action   action, 
        Input::Mod      mods)
{
    for(auto& func : m_keyListeners)
        func(key, scancode, action, mods);
}
void EventBus::DispatchCursorPosListener(f64 x, f64 y)
{
    for(auto& func : m_cursorPosListeners)
        func(x, y);
}
void EventBus::DispatchCursorEnterListener(bool entered)
{
    for(auto& func : m_cursorEnterListeners)
        func(entered);
}
void EventBus::DispatchMouseButtonListener(
        Input::MouseButton  mousebutton, 
        Input::Action       action, 
        Input::Mod          mods)
{
    for(auto& func : m_mouseButtonListeners)
        func(mousebutton, action, mods);
}
void EventBus::DispatchScrollbackListener(f64 x, f64 y)
{
    for(auto& func : m_scrollListeners)
        func(x, y);
}
void EventBus::DispatchWindowCloseListener()
{
    for(auto& func : m_windowCloseListeners)
        func();
}
void EventBus::DispatchWindowFocusListener(bool focused)
{
    for(auto& func : m_windowFocusListeners)
        func(focused);
}
void EventBus::DispatchGamepadConnectionListener(i32 jid, Input::GamepadConnection connection)
{
    for(auto& func : m_gamepadConnectionListeners)
        func(jid, connection);
}
void EventBus::DispatchGamepadButtonListener(Input::GamepadButton button, Input::Action action)
{
    for(auto& func : m_gamepadButtonListeners)
        func(button, action);
}
void EventBus::DispatchGamepadAxisListener(Input::GamepadAxis axis, f32 rawValue)
{
    for(auto& func : m_gamepadAxisListeners)
        func(axis, rawValue);
}

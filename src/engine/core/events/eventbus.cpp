#include "eventbus.hpp"

using namespace Core; 

EventBus& EventBus::GetInstance()
{
    static EventBus bus;
    return bus;
}

void EventBus::AddFramebufferListener(const Callback<i32, i32>&& func)
{
    if(func) { m_frameListeners.emplace_back(func); }
}
void EventBus::AddKeyListener(const Callback<Input::Key, i32, Input::Action, Input::Mod>&& func)
{
    if(func) { m_keyListeners.emplace_back(func); }
}
void EventBus::AddCursorPosListener(const Callback<f64, f64>&& func)
{
    if(func) { m_cursorPosListeners.emplace_back(func); }
}

void EventBus::AddCursorEnterListener(const Callback<bool>&& func)
{
    if(func) { m_cursorEnterListeners.emplace_back(func); }
}
void EventBus::AddMouseButtonListener(const Callback<Input::MouseButton, Input::Action, Input::Mod>&& func)
{
    if(func) { m_mouseButtonListeners.emplace_back(func); }
}
void EventBus::AddScrollbackListener(const Callback<f64, f64>&& func)
{
    if(func) { m_scrollListeners.emplace_back(func); }
}
void EventBus::AddWindowCloseListener(const Callback<>&& func)
{
    if(func) { m_windowCloseListeners.emplace_back(func); }
}
void EventBus::AddWindowFocusListener(const Callback<bool>&& func)
{
    if(func) { m_windowFocusListeners.emplace_back(func); }
}
void EventBus::AddGamepadConnectionListener(const Callback<i32, Input::GamepadConnection>&& func)
{
    if(func) { m_gamepadConnectionListeners.emplace_back(func); }
}
void EventBus::AddGamepadButtonListener(const Callback<Input::GamepadButton, Input::Action>&& func)
{
    if(func) { m_gamepadButtonListeners.emplace_back(func); }
}
void EventBus::AddGamepadAxisListener(const Callback<Input::GamepadAxis, f32>&& func)
{
    if (func) { m_gamepadAxisListeners.emplace_back(func); }
}

void EventBus::DispatchFramebufferListener(i32 width, i32 height)
{
    for(auto& func : m_frameListeners) 
        if(func) 
            func(width, height);
}
void EventBus::DispatchKeyListener(
        Input::Key      key, 
        i32             scancode, 
        Input::Action   action, 
        Input::Mod      mods)
{
    for(auto& func : m_keyListeners)
        if(func)
            func(key, scancode, action, mods);
}
void EventBus::DispatchCursorPosListener(f64 x, f64 y)
{
    for(auto& func : m_cursorPosListeners)
        if(func)
            func(x, y);
}
void EventBus::DispatchCursorEnterListener(bool entered)
{
    for(auto& func : m_cursorEnterListeners)
        if(func)
            func(entered);
}
void EventBus::DispatchMouseButtonListener(
        Input::MouseButton  mousebutton, 
        Input::Action       action, 
        Input::Mod          mods)
{
    for(auto& func : m_mouseButtonListeners)
        if(func)
            func(mousebutton, action, mods);
}
void EventBus::DispatchScrollbackListener(f64 x, f64 y)
{
    for(auto& func : m_scrollListeners)
        if(func)
            func(x, y);
}
void EventBus::DispatchWindowCloseListener()
{
    for(auto& func : m_windowCloseListeners)
        if(func)
            func();
}
void EventBus::DispatchWindowFocusListener(bool focused)
{
    for(auto& func : m_windowFocusListeners)
        if(func)
            func(focused);
}
void EventBus::DispatchGamepadConnectionListener(i32 jid, Input::GamepadConnection connection)
{
    for(auto& func : m_gamepadConnectionListeners)
        if(func)
            func(jid, connection);
}
void EventBus::DispatchGamepadButtonListener(Input::GamepadButton button, Input::Action action)
{
    for(auto& func : m_gamepadButtonListeners)
        if(func)
            func(button, action);
}
void EventBus::DispatchGamepadAxisListener(Input::GamepadAxis axis, f32 rawValue)
{
    for(auto& func : m_gamepadAxisListeners)
        if(func)
            func(axis, rawValue);
}

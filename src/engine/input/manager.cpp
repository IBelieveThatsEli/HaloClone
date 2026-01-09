#include "manager.hpp"

#include "runtime/events/eventbus.hpp"
#include <print>

using namespace Input;

Manager::Manager()
{
    Runtime::EventBus::GetInstance()
        .AddGamepadConnectionListener([this](i32 jid, GamepadConnection connection) {
                    if (connection == GamepadConnection::Connected)
                    {
                        std::print("Gamepad connected!\n");
                        OnGamepadConnected(jid);
                    }
                    else
                    {
                        std::print("Gamepad disconnected!\n");
                        OnGamepadDisconnected(jid);
                    }
                });
}

Manager::~Manager()
{
    DisableGamepad();
    DisableKeyboard();
    DisableMouse();
}

void Manager::Update(f32 dt)
{
    if(m_mouse)
        m_mouse->Update();

    if(m_keyboard)
        m_keyboard->Update();

    if(m_gamepad)
        m_gamepad->Update(dt);
}

void Manager::OnGamepadConnected(i32 jid)
{
    std::print("{} Gamepad Connected\n", jid);
    EnableGamepad(std::make_unique<Gamepad>(jid));
}
void Manager::OnGamepadDisconnected(i32 jid)
{
    if (m_gamepad && m_gamepad->GetID() == jid)
    {
        std::print("{} Gamepad Disconnected\n", jid);
        DisableGamepad();
    }
}

void Manager::EnableGamepad(std::unique_ptr<Gamepad> gamepad)
{
    if (!gamepad)
        return;
    m_gamepad = std::move(gamepad);

    Runtime::EventBus::GetInstance()
        .AddGamepadButtonListener([this](GamepadButton btn, Action action) {
                    m_gamepad->ButtonListener(btn, action);
                });

    Runtime::EventBus::GetInstance()
        .AddGamepadAxisListener([this](GamepadAxis axis, f32 rawValue) {
                    m_gamepad->AxisListener(axis, rawValue);
                });
}
void Manager::EnableKeyboard(std::unique_ptr<Keyboard> keyboard)
{
    if (!keyboard)
        return;
    m_keyboard = std::move(keyboard);

    Runtime::EventBus::GetInstance()
        .AddKeyListener([this](Input::Key key, i32 scancode, Input::Action action, Input::Mod mods) {
                    m_keyboard->OnButtonEvent(key, scancode, action, mods);
                });
}
void Manager::EnableMouse(std::unique_ptr<Mouse> mouse)
{
    if (!mouse)
        return;
    m_mouse = std::move(mouse);

    Runtime::EventBus::GetInstance()
        .AddMouseButtonListener([this](Input::MouseButton btn, Input::Action a, Input::Mod mods) {
                    m_mouse->OnButtonEvent(btn, 0, a, mods);
                });
    Runtime::EventBus::GetInstance()
        .AddCursorPosListener([this](f64 x, f64 y) {
                    m_mouse->OnMoveEvent(x, y);
                });
}

void Manager::DisableGamepad()
{
    if (m_gamepad)
    {
        m_gamepad.reset();
        m_gamepad = nullptr;
    }
}
void Manager::DisableKeyboard()
{
    if (m_keyboard)
    {
        m_keyboard.reset();
        m_keyboard = nullptr;
    }
}
void Manager::DisableMouse()
{
    if (m_mouse)
    {
        m_mouse.reset();
        m_mouse = nullptr;
    }
}

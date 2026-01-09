#include "eventbridge.hpp"

#include "runtime/events/eventbus.hpp"
#include "core/utils/types.hpp"

#include "input/types/action.hpp"
#include "input/types/gamepadbutton.hpp"
#include "input/types/gamepadconnection.hpp"
#include "input/types/mousebutton.hpp"
#include "input/types/key.hpp"
#include "input/types/mod.hpp"

static Input::Key ConvertSDLKey(SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_A         : return Input::Key::A;
        case SDLK_B         : return Input::Key::B;
        case SDLK_C         : return Input::Key::C;
        case SDLK_D         : return Input::Key::D;
        case SDLK_E         : return Input::Key::E;
        case SDLK_F         : return Input::Key::F;
        case SDLK_G         : return Input::Key::G;
        case SDLK_H         : return Input::Key::H;
        case SDLK_I         : return Input::Key::I;
        case SDLK_J         : return Input::Key::J;
        case SDLK_K         : return Input::Key::K;
        case SDLK_L         : return Input::Key::L;
        case SDLK_M         : return Input::Key::M;
        case SDLK_N         : return Input::Key::N;
        case SDLK_O         : return Input::Key::O;
        case SDLK_P         : return Input::Key::P;
        case SDLK_Q         : return Input::Key::Q;
        case SDLK_R         : return Input::Key::R;
        case SDLK_S         : return Input::Key::S;
        case SDLK_T         : return Input::Key::T;
        case SDLK_U         : return Input::Key::U;
        case SDLK_V         : return Input::Key::V;
        case SDLK_W         : return Input::Key::W;
        case SDLK_X         : return Input::Key::X;
        case SDLK_Y         : return Input::Key::Y;
        case SDLK_Z         : return Input::Key::Z;

        case SDLK_ESCAPE    : return Input::Key::Escape;
        case SDLK_SPACE     : return Input::Key::Space;
        case SDLK_RETURN    : return Input::Key::Enter;
        case SDLK_TAB       : return Input::Key::Tab;
        case SDLK_BACKSPACE : return Input::Key::Backspace;

        case SDLK_LEFT      : return Input::Key::Left;
        case SDLK_RIGHT     : return Input::Key::Right;
        case SDLK_UP        : return Input::Key::Up;
        case SDLK_DOWN      : return Input::Key::Down;

        default             : return Input::Key::Unknown; // fallback
    }
}

static Input::Mod ConvertSDLMods(SDL_Keymod mods)
{
    i32 result = (i32)Input::Mod::None;

    if (mods & (SDL_KMOD_LSHIFT | SDL_KMOD_RSHIFT))
        result |= (i32)Input::Mod::Shift;

    if (mods & (SDL_KMOD_LCTRL | SDL_KMOD_RCTRL))
        result |= (i32)Input::Mod::Control;

    if (mods & (SDL_KMOD_LALT | SDL_KMOD_RALT))
        result |= (i32)Input::Mod::Alt;

    if (mods & (SDL_KMOD_LGUI | SDL_KMOD_RGUI)) // Windows key / Cmd key
        result |= (i32)Input::Mod::Super;

    if (mods & SDL_KMOD_CAPS)
        result |= (i32)Input::Mod::CapsLock;

    if (mods & SDL_KMOD_NUM)
        result |= (i32)Input::Mod::NumLock;

    return (Input::Mod)result;
}

static Input::MouseButton ConvertSDLMouseButton(u8 button)
{
    switch (button)
    {
        case SDL_BUTTON_LEFT    : return Input::MouseButton::Left;
        case SDL_BUTTON_RIGHT   : return Input::MouseButton::Right;
        case SDL_BUTTON_MIDDLE  : return Input::MouseButton::Middle;
        case SDL_BUTTON_X1      : return Input::MouseButton::_1;
        case SDL_BUTTON_X2      : return Input::MouseButton::_2;
        default                 : return Input::MouseButton::Unknown;
    }
}

static Input::GamepadButton ConvertSDLGamepadButton(u8 b)
{
    switch (b)
    {
        case SDL_GAMEPAD_BUTTON_SOUTH           : return Input::GamepadButton::A;
        case SDL_GAMEPAD_BUTTON_EAST            : return Input::GamepadButton::B;
        case SDL_GAMEPAD_BUTTON_WEST            : return Input::GamepadButton::X;
        case SDL_GAMEPAD_BUTTON_NORTH           : return Input::GamepadButton::Y;

        case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER   : return Input::GamepadButton::LeftBumper;
        case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER  : return Input::GamepadButton::RightBumper;

        case SDL_GAMEPAD_BUTTON_BACK            : return Input::GamepadButton::Back;
        case SDL_GAMEPAD_BUTTON_START           : return Input::GamepadButton::Start;
        case SDL_GAMEPAD_BUTTON_GUIDE           : return Input::GamepadButton::Guide;

        case SDL_GAMEPAD_BUTTON_LEFT_STICK      : return Input::GamepadButton::LeftStick;
        case SDL_GAMEPAD_BUTTON_RIGHT_STICK     : return Input::GamepadButton::RightStick;

        case SDL_GAMEPAD_BUTTON_DPAD_UP         : return Input::GamepadButton::DPadUp;
        case SDL_GAMEPAD_BUTTON_DPAD_RIGHT      : return Input::GamepadButton::DPadRight;
        case SDL_GAMEPAD_BUTTON_DPAD_DOWN       : return Input::GamepadButton::DPadDown;
        case SDL_GAMEPAD_BUTTON_DPAD_LEFT       : return Input::GamepadButton::DPadLeft;

        default                                 : return Input::GamepadButton::COUNT; // unknown
    }
}

static Input::GamepadAxis ConvertSDLGamepadAxis(u8 a)
{
    switch (a)
    {
        case SDL_GAMEPAD_AXIS_LEFTX         : return Input::GamepadAxis::LeftStickX;
        case SDL_GAMEPAD_AXIS_LEFTY         : return Input::GamepadAxis::LeftStickY;
        case SDL_GAMEPAD_AXIS_RIGHTX        : return Input::GamepadAxis::RightStickX;
        case SDL_GAMEPAD_AXIS_RIGHTY        : return Input::GamepadAxis::RightStickY;
        case SDL_GAMEPAD_AXIS_LEFT_TRIGGER  : return Input::GamepadAxis::LeftTrigger;
        case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER : return Input::GamepadAxis::RightTrigger;

        default                             : return Input::GamepadAxis::COUNT; // unknown
    }
}

using namespace SDL3;

void EventBridge::PollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        EventBridge::ProcessEvent(event);
    }
}

void EventBridge::ProcessEvent(const SDL_Event &e)
{
    auto& bus = Runtime::EventBus::GetInstance();

    switch (e.type)
    {
        case SDL_EVENT_QUIT:
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            bus.DispatchWindowCloseListener();
        break;

        case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
        {
            i32 fbWidth  = e.window.data1;
            i32 fbHeight = e.window.data2;

            bus.DispatchFramebufferListener(fbWidth, fbHeight);
        }
        break;

        case SDL_EVENT_WINDOW_FOCUS_GAINED:
            bus.DispatchWindowFocusListener(true);
        break;

        case SDL_EVENT_WINDOW_FOCUS_LOST:
            bus.DispatchWindowFocusListener(false);
        break;

        case SDL_EVENT_KEY_DOWN:
            bus.DispatchKeyListener(
                ConvertSDLKey(e.key.key),
                0,
                Input::Action::Press,
                Input::Mod::None
            );
        break;

        case SDL_EVENT_KEY_UP:
            bus.DispatchKeyListener(
                ConvertSDLKey(e.key.key),
                0,
                Input::Action::Release,
                Input::Mod::None
            );
        break;

        case SDL_EVENT_MOUSE_MOTION:
            bus.DispatchCursorPosListener(
                static_cast<f64>(e.motion.x),
                static_cast<f64>(e.motion.y)
            );
        break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP:
            bus.DispatchMouseButtonListener(
                ConvertSDLMouseButton(e.button.button),
                e.button.down ? Input::Action::Press : Input::Action::Release,
                Input::Mod::None
            );
        break;

        case SDL_EVENT_MOUSE_WHEEL:
            bus.DispatchScrollbackListener(
                static_cast<f64>(e.wheel.x),
                static_cast<f64>(e.wheel.y)
            );
        break;

        // --- GAMEPAD ---

        case SDL_EVENT_GAMEPAD_ADDED:
        {
            SDL_Gamepad* pad = SDL_OpenGamepad(e.gdevice.which);

            bus.DispatchGamepadConnectionListener(
                e.gdevice.which,
                Input::GamepadConnection::Connected
            );
        }
        break;

        case SDL_EVENT_GAMEPAD_REMOVED:
            bus.DispatchGamepadConnectionListener(
                e.gdevice.which,
                Input::GamepadConnection::Disconnected
            );
        break;

        case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
        case SDL_EVENT_GAMEPAD_BUTTON_UP:
            bus.DispatchGamepadButtonListener(
                ConvertSDLGamepadButton(e.gbutton.button),
                e.gbutton.down ? Input::Action::Press : Input::Action::Release
            );
        break;

        case SDL_EVENT_GAMEPAD_AXIS_MOTION:
            bus.DispatchGamepadAxisListener(
                ConvertSDLGamepadAxis(e.gaxis.axis),
                e.gaxis.value
            );
        break;
    } 
}

// void EventBridge::UpdateGamepads()
// {

// }

#pragma once

#include "utils/types.hpp"

namespace Input
{
    enum class GamepadButton : i32 
    {
        A,
        B,
        X,
        Y,

        LeftBumper,
        RightBumper,

        Back,
        Start,
        Guide,          // “Home / PS button”

        LeftStick,
        RightStick,

        DPadUp,
        DPadRight,
        DPadDown,
        DPadLeft,

        // Extra: Some controllers have these
        Misc1,  // Capture / Share
        Paddle1,
        Paddle2,
        Paddle3,
        Paddle4,

        COUNT // Keep last — total number of buttons
    };

    inline const char* ToString(GamepadButton button)
    {
        switch(button) 
        {
            case GamepadButton::A           : return "A";
            case GamepadButton::B           : return "B";
            case GamepadButton::X           : return "X";
            case GamepadButton::Y           : return "Y";
            case GamepadButton::LeftBumper  : return "LeftBumper";
            case GamepadButton::RightBumper : return "RightBumper";
            case GamepadButton::Back        : return "Back";
            case GamepadButton::Start       : return "Start";
            case GamepadButton::Guide       : return "Guide";
            case GamepadButton::LeftStick   : return "LeftStick";
            case GamepadButton::RightStick  : return "RightStick";
            case GamepadButton::DPadUp      : return "DPadUp";
            case GamepadButton::DPadRight   : return "DPadRight";
            case GamepadButton::DPadDown    : return "DPadDown";
            case GamepadButton::DPadLeft    : return "DPadLeft";
            case GamepadButton::Misc1       : return "Misc1";
            case GamepadButton::Paddle1     : return "Paddle1";
            case GamepadButton::Paddle2     : return "Paddle2";
            case GamepadButton::Paddle3     : return "Paddle3";
            case GamepadButton::Paddle4     : return "Paddle4";
            default                         : return "UnknownButton";
        }
    }
} // Input

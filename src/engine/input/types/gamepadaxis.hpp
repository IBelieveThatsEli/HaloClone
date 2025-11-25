#pragma once

#include "utils/types.hpp"

namespace Input
{
    enum class GamepadAxis : i32 {
        LeftStickX,
        LeftStickY,

        RightStickX,
        RightStickY,

        LeftTrigger,
        RightTrigger,

        COUNT
    };
} // Input

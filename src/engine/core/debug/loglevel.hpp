#pragma once

#include "core/utils/types.hpp"

namespace Core
{
    enum class LogLevel : u8 
    {
        Trace, 
        Info,
        Warn,
        Error,
        Fatal
    };

    enum class LogCategory : u8
    {
        Core,
        Renderer,
        Asset,
        Scene
    };
} // Core

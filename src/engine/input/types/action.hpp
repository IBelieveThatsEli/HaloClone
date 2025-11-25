#pragma once

#include "utils/types.hpp"

namespace Input
{
    enum Action : i32 
    {
        Release = 0,
        Press   = 1,
        Repeat  = 2
    };
} // Input

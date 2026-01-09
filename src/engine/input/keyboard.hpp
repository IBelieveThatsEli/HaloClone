#pragma once

#include "basebutton.hpp"

#include "types/key.hpp"

namespace Input
{
    class Keyboard final : public BaseButton<Key> {};
} // Input

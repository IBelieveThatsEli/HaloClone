#pragma once

#include "basebutton.hpp"

#include "types/key.hpp"

namespace Input
{
    class Keyboard : public BaseButton<Key> {};
} // Input

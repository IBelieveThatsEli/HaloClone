#pragma once

#include <SDL3/SDL.h>

namespace SDL3
{
    class EventBridge
    {
        public:
            static void ProcessEvent(const SDL_Event& e);
            static void UpdateGamepads();
    };
} // SDL3

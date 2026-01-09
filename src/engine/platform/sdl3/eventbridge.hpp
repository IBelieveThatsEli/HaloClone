#pragma once

#include "platform/ieventbridge/ieventbridge.hpp"

#include <SDL3/SDL.h>

namespace SDL3
{
    // class EventBridge final
    // {
    //     public:
    //         static void ProcessEvent(const SDL_Event& e);
    //         static void UpdateGamepads();
    // };
    
    class EventBridge final : public Platform::IEventBridge
    {
        public:
            EventBridge() = default;

            void PollEvents() override;
        
        private:
            void ProcessEvent(const SDL_Event& e);
    };
} // SDL3

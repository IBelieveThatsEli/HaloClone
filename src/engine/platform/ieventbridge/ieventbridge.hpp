#pragma once

namespace Platform
{
    class IEventBridge
    {
        public:
            virtual ~IEventBridge() = default;

            virtual void Init(void* windowHandle) = 0;

            virtual void PollEvents() = 0;
    };
} // Platform
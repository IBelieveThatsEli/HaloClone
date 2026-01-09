#pragma once

namespace Platform
{
    class IEventBridge
    {
        public:
            virtual ~IEventBridge() = default;
            virtual void PollEvents() = 0;
    };
} // Platform
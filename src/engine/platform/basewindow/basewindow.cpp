#include "basewindow.hpp"

#include "runtime/events/eventbus.hpp"

using namespace Platform;

BaseWindow::BaseWindow(const Properties& properties) 
    : m_properties(properties)
{
    for (auto& func : m_framebufferCallbacks)
        Runtime::EventBus::GetInstance()
            .AddFramebufferListener([&](i32 w, i32 y) { func(w, y); });

    for (auto& func : m_focusCallbacks)
        Runtime::EventBus::GetInstance()
            .AddWindowFocusListener([&](bool focused) { func(focused); });
}

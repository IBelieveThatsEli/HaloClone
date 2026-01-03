#include "basewindow.hpp"

#include "core/events/eventbus.hpp"

using namespace Core;

BaseWindow::BaseWindow(const Properties& properties) 
    : m_properties(properties)
{
    for (auto& func : m_framebufferCallbacks)
        EventBus::GetInstance()
            .AddFramebufferListener([&](i32 w, i32 y) { func(w, y); });

    for (auto& func : m_closeCallbacks)
        EventBus::GetInstance()
            .AddWindowCloseListener([&]() { func(); });

    for (auto& func : m_focusCallbacks)
        EventBus::GetInstance()
            .AddWindowFocusListener([&](bool focused) { func(focused); });
}

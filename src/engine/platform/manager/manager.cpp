#include "manager.hpp"

#include "platform/glfw/window.hpp"
#include "platform/sdl3/window.hpp"

using namespace Platform;

void Manager::Create(Core::WindowAPI api, Core::BaseWindow::Properties props)
{
    m_api = api;

    switch (m_api)
    {
        case Core::WindowAPI::SDL3:
            m_window = std::make_unique<SDL3::Window>(props);
            break;
        case Core::WindowAPI::GLFW:
            m_window = std::make_unique<GLFW::Window>(props);
            break;
    }
}

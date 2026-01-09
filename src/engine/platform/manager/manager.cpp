#include "manager.hpp"

#include "platform/glfw/window.hpp"
#include "platform/sdl3/window.hpp"

#include "platform/glfw/eventbridge.hpp"
#include "platform/sdl3/eventbridge.hpp"

using namespace Platform;

void Manager::Create(
    const Core::WindowAPI& api, 
    const BaseWindow::Properties& props
)
{
    m_api = api;

    switch (m_api)
    {
        case Core::WindowAPI::SDL3:
            m_window = std::make_unique<SDL3::Window>(props);
            m_eventBridge = std::make_unique<SDL3::EventBridge>();
            break;

        case Core::WindowAPI::GLFW:
            m_window = std::make_unique<GLFW::Window>(props);
            m_eventBridge = std::make_unique<GLFW::EventBridge>(static_cast<GLFWwindow*>(m_window->GetHandle()));
            break;
    }
    }

void Manager::ChangeGraphicsAPI(const Core::GraphicsAPI& api)
{
    m_window->ChangeGraphicsAPI(api);
}

void Manager::Update()
{
    m_eventBridge->PollEvents();
}
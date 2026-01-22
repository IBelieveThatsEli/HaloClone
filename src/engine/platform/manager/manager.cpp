#include "manager.hpp"

using namespace Platform;

#if defined(ENGINE_USE_GLFW)
    #include "platform/glfw/window.hpp"
    #include "platform/glfw/eventbridge.hpp"
    
    using PlatformWindow    = GLFW::Window;
    using EventBridge       = GLFW::EventBridge;
#elif defined(ENGINE_USE_SDL)
    #include "platform/sdl3/window.hpp"
    #include "platform/sdl3/eventbridge.hpp"

    using PlatformWindow    = SDL3::Window;
    using EventBridge       = SDL3::EventBridge;
#endif

WindowID Manager::CreateWindow(const BaseWindow::Properties& properties)
{
    // m_windows = std::make_unique<PlatformWindow>(properties);
    // m_eventBridge = std::make_unique<EventBridge>();

    // m_eventBridge.Init(m_window->GetHandle());
}

void Manager::DestoryWindow(WindowID id)
{

}

// void Manager::Create(
//     const Core::WindowAPI& api, 
//     const BaseWindow::Properties& props
// )
// {
//     m_api = api;

    // switch (m_api)
    // {
    //     case Core::WindowAPI::SDL3:
    //         m_window        = std::make_unique<SDL3::Window>(props);
    //         m_eventBridge   = std::make_unique<SDL3::EventBridge>();
    //         break;

    //     case Core::WindowAPI::GLFW:
    //         m_window        = std::make_unique<GLFW::Window>(props);
    //         m_eventBridge   = std::make_unique<GLFW::EventBridge>(static_cast<GLFWwindow*>(m_window->GetHandle()));
    //         break;
    // }
//     }

// void Manager::ChangeGraphicsAPI(const Core::GraphicsAPI& api)
// {
//     m_window->ChangeGraphicsAPI(api);
// }

// void Manager::Update()
// {
//     m_eventBridge->PollEvents();
// }


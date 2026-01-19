#include "engine.hpp"

#include "runtime/events/eventbus.hpp"

Engine* Engine::GetInstance()
{
    static Engine engine;
    return &engine;
}

Engine::Engine()
{
    m_platformManager = std::make_unique<Platform::Manager>();
    
    Platform::BaseWindow::Properties props = 
    { 
        .graphicsAPI = Core::GraphicsAPI::OpenGL
    };

    m_platformManager->Create(Core::WindowAPI::SDL3, props);

    Runtime::EventBus::GetInstance()
        .AddWindowCloseListener([&]() { m_shutdownRequest = true; });

    Runtime::EventBus::GetInstance()
        .AddWindowCloseListener([&](){
            m_platformManager->GetWindow().Close();
        })
}

Engine::~Engine()
{
    if (m_platformManager)
    {
        m_platformManager.reset();
        m_platformManager = nullptr;
    }

    // if (m_renderer)
    // {
    //     m_renderer.reset();
    //     m_renderer = nullptr;
    // }
}

Platform::Manager* Engine::GetPlatformManager() noexcept
{
    return m_platformManager.get();
}

void Engine::Update(f32 dt)
{
    m_platformManager->Update();
}
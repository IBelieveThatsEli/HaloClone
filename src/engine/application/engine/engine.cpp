#include "engine.hpp"

// #include "renderer/opengl/renderer/renderer.hpp"

#include "runtime/events/eventbus.hpp"

Engine* Engine::GetInstance()
{
    static Engine engine;
    return &engine;
}

Engine::Engine()
{
    m_platformManager = std::make_unique<Platform::Manager>();
    auto props = Platform::BaseWindow::Properties { .graphicsAPI = Core::GraphicsAPI::OpenGL};
    m_platformManager->Create(Core::WindowAPI::SDL3, props);

    Runtime::EventBus::GetInstance()
        .AddWindowCloseListener([&]() { m_shutdownRequest = true; });

    Runtime::EventBus::GetInstance()
        .AddKeyListener([&](Input::Key key, i32, Input::Action action, Input::Mod mod) {
            static bool flag = false;
            if ((key == Input::Key::F) && (action == Input::Action::Press))
            {
                auto props_ = m_platformManager->GetWindow()->GetProperties();
                if (!flag)
                    m_platformManager->Create(Core::WindowAPI::SDL3, props_);
                else
                    m_platformManager->Create(Core::WindowAPI::GLFW, props_);
            }
        });
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
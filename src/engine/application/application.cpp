#include "application.hpp"

#include "core/api/api.hpp"
#include "core/engine/engine.hpp"
#include "scene/scene.hpp"
#include "scene/sceneserializer/sceneserializer.hpp"

#include <format>

using namespace Engine;

Application::Application(
        const Core::GraphicsAPI&& graphicsAPI, 
        const Core::WindowAPI&& windowAPI)
{
    Core::BaseWindow::Properties props = Core::BaseWindow::Properties { .graphicsAPI = graphicsAPI };
    m_platformManager.Create(windowAPI, props);

    m_engine = std::make_unique<Core::Engine>(graphicsAPI);
}

Application::~Application()
{
    if (m_engine)
    {
        m_engine.reset();
        m_engine = nullptr;
    }
}

void Application::ChangeWindowAPI(const Core::WindowAPI&& api)
{
    // Want to keep the previous state of the window when changing api's.
    const Core::BaseWindow::Properties& prevProperties = m_platformManager.GetWindow()->GetProperties();

    m_platformManager.Create(api, prevProperties);
}

void Application::ChangeGraphicsAPI(const Core::GraphicsAPI&& api)
{
    m_platformManager.ChangeGraphicsAPI(api);
}

void Application::LoadScene(std::string_view path)
{
    std::shared_ptr<Scene::Scene> scene = std::make_shared<Scene::Scene>("MainScene");

    if (!Scene::SceneSerializer::Deserialize(*scene, path))
        throw std::runtime_error(std::format("Failed to deserialize scene {}\n", path.data()));

    m_engine->SetScene(scene);
}

void Application::Run()
{
    while(m_platformManager.GetWindow()->IsOpen())
    {
        m_platformManager.GetWindow()->PollEvents();
    }
}

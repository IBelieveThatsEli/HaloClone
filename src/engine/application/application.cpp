#include "application.hpp"

#include "core/api/api.hpp"
#include "core/engine/engine.hpp"
#include "scene/scene.hpp"
#include "scene/sceneserializer/sceneserializer.hpp"
#include <format>

using namespace Engine;

Application::Application(Core::GraphicsAPI graphicsAPI, Core::WindowAPI windowAPI)
{
    m_platformManager.Create(windowAPI, Core::BaseWindow::Properties { .graphicsAPI = graphicsAPI });

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

#include "engine.hpp"

#include "scene/scene.hpp"

using namespace Core;

Engine::Engine(Core::GraphicsAPI graphicsAPI)
    : m_graphicsAPI(graphicsAPI)
{
}

Engine::~Engine()
{
}

void Engine::SetScene(std::shared_ptr<Scene::Scene> scene)
{
    m_activeScene = std::move(scene);
}

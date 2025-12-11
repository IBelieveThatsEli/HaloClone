#include "engine.hpp"

#include "scene/scene.hpp"
#include "renderer/opengl/renderer/renderer.hpp"

using namespace Core;

Engine::Engine(Core::GraphicsAPI graphicsAPI)
    : m_graphicsAPI(graphicsAPI)
{
    m_renderer = std::make_unique<OpenGL::Renderer>();
}

Engine::~Engine()
{
}

void Engine::SetScene(std::shared_ptr<Scene::Scene> scene)
{
    m_activeScene = std::move(scene);
}

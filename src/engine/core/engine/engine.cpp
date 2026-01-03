#include "engine.hpp"

#include "scene/scene.hpp"
#include "renderer/opengl/renderer/renderer.hpp"

using namespace Core;

Engine::Engine(const Core::GraphicsAPI& api)
    : m_graphicsAPI(api)
{
    SetGraphicsAPI(api);
}

Engine::~Engine()
{
}

void Engine::SetGraphicsAPI(const Core::GraphicsAPI& api)
{
    if (api == Core::GraphicsAPI::OpenGL)
        m_renderer = std::make_unique<OpenGL::Renderer>();
}

void Engine::SetScene(std::shared_ptr<Scene::Scene> scene)
{
    m_activeScene = std::move(scene);
}

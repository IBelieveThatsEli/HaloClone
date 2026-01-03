#include "renderer.hpp"

#include <volk.h>

#include <stdexcept>

using namespace Vulkan;

Renderer::Renderer()
{
    if (volkInitialize() != VK_SUCCESS)
        throw std::runtime_error("Failed to intialize volk");
}

Renderer::~Renderer()
{

}

void Renderer::SetScene(Scene::Scene& scene)
{

}

void Renderer::Render()
{

}

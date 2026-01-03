#include "renderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

using namespace OpenGL;

Renderer::Renderer()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");
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

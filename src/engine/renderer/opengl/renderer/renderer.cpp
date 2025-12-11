#include "renderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

static const char* default_vs = R"(
#version 400 core
layout(location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(aPos, 1.0);
}
)";

static const char* default_fs = R"(
#version 400 core
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
)";

using namespace OpenGL;

Renderer::Renderer()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }
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

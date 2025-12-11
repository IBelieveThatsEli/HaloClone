#include "shader.hpp"

#include <fstream>

using namespace Renderer;

Shader::Shader(std::string_view name, std::string_view path, ShaderType type)
    : m_name(name), m_path(path), m_type(type)
{}

bool Shader::LoadFromFile()
{
    std::ifstream file(m_path.data(), std::ios::ate | std::ios::binary);
    if (!file.is_open())
        return false;

    size_t size = file.tellg();
    m_binary.resize(size);

    file.seekg(0);
    file.read(m_binary.data(), size);
    file.close();

    return true;
}

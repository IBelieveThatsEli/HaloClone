#include "shadermanager.hpp"

using namespace Renderer;

Shader* ShaderManager::GetShader(std::string_view name) const noexcept 
{
    auto it = m_shaders.find(name);
    return (it != m_shaders.end()) ? it->second.get() : nullptr;
}

bool ShaderManager::ReloadShader(std::string_view name) const noexcept
{
    Shader* shader = GetShader(name);
    if (!shader) 
        return false;
    return shader->LoadFromFile();
}

void ShaderManager::ReloadAll()
{
    for (auto& [name, _] : m_shaders)
        bool res = ReloadShader(name);
}

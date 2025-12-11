#pragma once

#include "shader.hpp"

#include <unordered_map>
#include <memory>

namespace Renderer
{
    class ShaderManager
    {
        public:
            template<typename ShaderBackend, typename ...Args>
            [[nodiscard]] ShaderBackend* LoadShader(std::string_view name, Args&&... args)
            {
                auto shader = std::make_unique<ShaderBackend>(std::forward<Args>(args)...);
                ShaderBackend* ptr = shader.get();
                m_shaders[name.data()] = std::move(shader);
                return ptr;
            }

            [[nodiscard]] Shader* GetShader(std::string_view name) const noexcept;

            [[nodiscard]] bool ReloadShader(std::string_view name) const noexcept;

            void ReloadAll();

        private:
            std::unordered_map<std::string_view, std::unique_ptr<Shader>> m_shaders;
    };
} // Renderer

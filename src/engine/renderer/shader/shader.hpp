#pragma once

#include <vector>
#include <string_view>

namespace Renderer
{
    class Shader
    {
        public:
            enum ShaderType
            {
                Compute, Vertex, Fragment
            };

            Shader() = default;
            Shader(std::string_view name, std::string_view path, ShaderType type);

            ~Shader() = default;

            [[nodiscard]] bool LoadFromFile();

            [[nodiscard]] std::string_view          GetName      ()     const noexcept { return m_name; }
            [[nodiscard]] std::string_view          GetFilePath  ()     const noexcept { return m_path; }
            [[nodiscard]] ShaderType                GetShaderType()     const noexcept { return m_type; }
            [[nodiscard]] const std::vector<char>&  GetBinaryData()     const noexcept { return m_binary; }

        protected:
            std::string_view m_name;
            std::string_view m_path;
            ShaderType m_type;
            std::vector<char> m_binary;
    };
} // Renderer

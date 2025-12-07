#pragma once

#include "utils/types.hpp"

#include <string_view>
#include <vector>
#include <glm/glm.hpp>

namespace Assets
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

    struct Submesh
    {
        u32                     indexOffset;
        u32                     indexCount;
        std::string_view        name;
    };

    struct Mesh
    {
        std::vector<Vertex>     vertices;
        std::vector<u32>        indices;

        std::vector<Submesh>    submeshes;

        std::string_view        sourceFile;
    };
} // Assets

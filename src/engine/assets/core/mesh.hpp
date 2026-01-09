/**
 * @file    mesh.hpp
 * @author  EMP "Ekam"
 * @brief   Declares core mesh data structures used by the Asset Subsystem.
 * 
 * This file defines CPU-side representations of mesh data, including
 * vertex attributes, index buffers, and submesh ranges. These structures
 * are owned and managed by the Asset subsystem and are intended to be
 * consumed by higher-level systems such as the Scene and Renderer.
 *
 * The types declared here are purely data-oriented and contain no
 * rendering or platform-specific logic.
 * 
 * @date    2026
 */


#pragma once

#include "core/utils/types.hpp"

#include <string_view>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace Assets
{
    /**
     * @struct Vertex
     * @brief  Represents a single vertex within a mesh.
     * 
     * A Vertex stores per-vertex attribute data such as position, normal,
     * texture coordinates, and any additional attributes required by the
     * rendering pipeline. Vertex data is stored in CPU memory and later
     * uploaded to GPU buffers by the Renderer subsystem.
     * 
     */

    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

    /**
     * @struct Submesh
     * @brief  Describes a contiguous range of indices within a mesh.
     * 
     * A Submesh allows a single Mesh to be logically divided into multiple
     * renderable sections, each potentially associated with different
     * materials or rendering states. Submeshes reference index ranges
     * rather than owning vertex data.
     * 
     */

    struct Submesh
    {
        u32                     indexOffset;
        u32                     indexCount;
        std::string_view        name;
    };

    /**
     * @struct Mesh
     * @brief  Aggregates vertex and index data describing a complete mesh asset.
     * 
     * A Mesh contains CPU-side vertex and index buffers, optional submesh
     * definitions, and metadata describing the asset's source. Mesh objects
     * are owned by the Asset subsystem and may be shared across multiple
     * scenes or entities.
     *
     * The Mesh structure does not perform rendering and does not manage GPU
     * resources. GPU-side representations are created and managed by the
     * Renderer subsystem.
     * 
     */

    struct Mesh
    {
        std::vector<Vertex>     vertices;
        std::vector<u32>        indices;

        std::vector<Submesh>    submeshes;

        std::string_view        sourceFile;
    };
} // Assets

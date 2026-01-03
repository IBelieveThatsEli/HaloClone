#pragma once

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <string_view>
#include <stdexcept>
#include <tiny_gltf.h>

#include "assets/core/mesh.hpp"

namespace Assets::Loaders
{
    inline Assets::Mesh LoadGLTF(std::string_view path)
    {
        tinygltf::Model model;
        tinygltf::TinyGLTF loader;
        std::string err, warn;

        Assets::Mesh mesh;

        bool ok = loader.LoadBinaryFromFile(&model, &err, &warn, std::string(path)) ||
                  loader.LoadASCIIFromFile(&model, &err, &warn, std::string(path));

        if(!ok)
            throw std::runtime_error("TinyGLTF failed to load: " + err);

        // We'll load just the first primitive for now
        const tinygltf::Mesh& gltfMesh = model.meshes[0];
        const tinygltf::Primitive& primitive = gltfMesh.primitives[0];

        // ----- POSITIONS -----
        {
            const tinygltf::Accessor& accessor = model.accessors[primitive.attributes.at("POSITION")];
            const tinygltf::BufferView& view = model.bufferViews[accessor.bufferView];
            const tinygltf::Buffer& buffer = model.buffers[view.buffer];

            const float* data = reinterpret_cast<const float*>(&buffer.data[accessor.byteOffset + view.byteOffset]);
            mesh.vertices.resize(accessor.count);

            for(size_t i = 0; i < accessor.count; i++)
                mesh.vertices[i].position = glm::vec3(data[i*3+0], data[i*3+1], data[i*3+2]);
        }

        // ----- INDICES -----
        {
            const tinygltf::Accessor& accessor = model.accessors[primitive.indices];
            const tinygltf::BufferView& view = model.bufferViews[accessor.bufferView];
            const tinygltf::Buffer& buffer = model.buffers[view.buffer];

            mesh.indices.resize(accessor.count);

            // supports uint16 or uint32
            if(accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
                const u16* data = reinterpret_cast<const u16*>(&buffer.data[accessor.byteOffset + view.byteOffset]);
                for(size_t i=0;i<accessor.count;i++) mesh.indices[i] = data[i];
            } else {
                const u32* data = reinterpret_cast<const u32*>(&buffer.data[accessor.byteOffset + view.byteOffset]);
                for(size_t i=0;i<accessor.count;i++) mesh.indices[i] = data[i];
            }
        }

        mesh.sourceFile = path;
        return mesh;
    }
} // Assets::Loaders

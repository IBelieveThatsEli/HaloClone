#pragma once

#include "assets/mesh.hpp"

#include <functional>
#include <string_view>

namespace Assets
{
    class MeshLibrary
    {
        public:
            using LoaderFunc = std::function<Mesh(std::string_view)>;

            static MeshLibrary& Get();

            void SetLoader(LoaderFunc loader);

            u32 LoadMesh(std::string_view path);

            void Clear();

        private:
            MeshLibrary();

            std::unordered_map<u32, Mesh> m_meshes;
            std::unordered_map<std::string_view, u32> m_pathToID;

            LoaderFunc m_loaderFunc = nullptr;

            u32 m_lastID = 0;
    };
} // Assets

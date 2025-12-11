#include "meshlibrary.hpp"

#include "assets/loaders/tinygltf.hpp"

#include <stdexcept>

namespace Assets
{
    MeshLibrary& MeshLibrary::Get()
    {
        static MeshLibrary meshLibrary;
        return meshLibrary;
    }

    MeshLibrary::MeshLibrary()
    {
        m_loaderFunc = Loaders::LoadGLTF;
    }

    void MeshLibrary::SetLoader(LoaderFunc loader)
    {
        m_loaderFunc = loader;
    }

    u32 MeshLibrary::LoadMesh(std::string_view path)
    {
        if (auto it = m_pathToID.find(path); it != m_pathToID.end())
            return it->second;

        if (!m_loaderFunc)
            throw std::runtime_error("MeshLibrary has no loader set");

        Mesh mesh = m_loaderFunc(path);
        u32 id = ++m_lastID;

        m_meshes[id] = std::move(mesh);
        m_pathToID[path] = id;
        
        return id;
    }

    void MeshLibrary::Clear()
    {
        m_meshes.clear();
        m_pathToID.clear();
        m_lastID = 0;
    }
} // Assets

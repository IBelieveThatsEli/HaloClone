#include "meshlibrary.hpp"
#include "assets/loaders/tinygltf.hpp"

#include <format>
#include <stdexcept>

using namespace Assets;

MeshLibrary& MeshLibrary::GetInstance()
{
    static MeshLibrary meshLib;

    meshLib.SetLoader(Loaders::LoadGLTF);

    return meshLib;
}


MeshLibrary::MeshLibrary()
    : m_nextId(1u) 
{}

MeshLibrary::~MeshLibrary()
{
    ClearAll();
}

void MeshLibrary::SetLoader(LoaderFunc loader)
{
    std::lock_guard lock(m_mutex);
    m_loader = std::move(loader);
}

void MeshLibrary::SetGPUUploadCallback(GPUUploadFunc uploadCb)
{
    std::lock_guard lock(m_mutex);
    m_gpuUpload = std::move(uploadCb);
}

void MeshLibrary::SetGPUDestroyCallback(GPUDestroyFunc destroyCb)
{
    std::lock_guard lock(m_mutex);
    m_gpuDestroy = std::move(destroyCb);
}

MeshHandle MeshLibrary::CreateHandle()
{
    uint32_t id = m_nextId.fetch_add(1u, std::memory_order_relaxed);
    MeshHandle h; h.id = id;
    return h;
}

MeshHandle MeshLibrary::LoadMesh(std::string_view path)
{
    if (path.empty()) 
        return MeshHandle{0};


    {
        std::lock_guard lock(m_mutex);
        auto it = m_pathToHandle.find(path);
        if (it != m_pathToHandle.end()) {
            MeshHandle h = it->second;
            auto entIt = m_entries.find(h);
            if (entIt != m_entries.end()) {
                entIt->second.refCount += 1;
                return h;
            }
        }
    }

    LoaderFunc loaderCopy;
    {
        std::lock_guard lock(m_mutex);
        loaderCopy = m_loader;
    }

    if (!loaderCopy) 
        throw std::runtime_error("MeshLibrary::LoadMesh called but no loader registered.");

    Mesh meshCpu;
    try 
    {
        meshCpu = loaderCopy(path);
    } 
    catch (const std::exception& e) 
    {
        throw std::runtime_error(std::format("Mesh loader failed: {}\n", e.what()));
    }

    meshCpu.sourceFile = path;
    auto meshPtr = std::make_shared<Mesh>(std::move(meshCpu));

    MeshHandle handle = CreateHandle();
    {
        std::lock_guard lock(m_mutex);
        Entry entry;
        entry.mesh = meshPtr;
        entry.refCount = 1;
        entry.path = path;

        m_entries.emplace(handle, std::move(entry));
        m_pathToHandle.emplace(path, handle);
    }

    GPUUploadFunc gpuUploadCopy;
    {
        std::lock_guard lock(m_mutex);
        gpuUploadCopy = m_gpuUpload;
    }

    if (gpuUploadCopy)
        gpuUploadCopy(handle, *meshPtr);

    return handle;
}

MeshHandle MeshLibrary::GetHandleForPath(std::string_view path) const
{
    std::lock_guard lock(m_mutex);
    
    auto it = m_pathToHandle.find(path);
    
    if (it == m_pathToHandle.end()) 
        return MeshHandle{0};
    
    return it->second;
}

MeshLibrary::MeshPtr MeshLibrary::Get(MeshHandle handle) const
{
    if (!handle) 
        return nullptr;
    
    std::lock_guard lock(m_mutex);
    auto it = m_entries.find(handle);

    if (it == m_entries.end()) 
        return nullptr;
    return it->second.mesh;
}

void MeshLibrary::Release(MeshHandle handle)
{
    if (!handle) 
        return;

    std::lock_guard lock(m_mutex);
    auto it = m_entries.find(handle);
    
    if (it == m_entries.end()) 
        return;

    if (it->second.refCount > 0) 
        --(it->second.refCount);
}

bool MeshLibrary::Exists(MeshHandle handle) const
{
    if (!handle) 
        return false;
    std::lock_guard lock(m_mutex);
    return m_entries.find(handle) != m_entries.end();
}

void MeshLibrary::DestroyEntryInternal(MeshHandle handle)
{
    auto it = m_entries.find(handle);
    if (it == m_entries.end()) return;

    GPUDestroyFunc gpuDestroyCopy;
    std::string_view path;
    {
        std::lock_guard lock(m_mutex);
        gpuDestroyCopy = m_gpuDestroy;
        path = it->second.path;
    }

    if (gpuDestroyCopy)
        gpuDestroyCopy(handle);
    {
        std::lock_guard lock(m_mutex);
        m_pathToHandle.erase(path);
        m_entries.erase(handle);
    }
}

void MeshLibrary::ClearUnused()
{
    std::vector<MeshHandle> toDestroy;
    {
        std::lock_guard lock(m_mutex);
        toDestroy.reserve(m_entries.size());

        for (auto const& [h, entry] : m_entries) 
        {
            if (entry.refCount == 0) 
            {
                toDestroy.push_back(h);
            }
        }
    }

    for (auto h : toDestroy) 
    {
        DestroyEntryInternal(h);
    }
}

void MeshLibrary::ClearAll()
{

    std::vector<MeshHandle> all;
    {
        std::lock_guard lock(m_mutex);
        all.reserve(m_entries.size());
        for (auto const& [h, _] : m_entries) all.push_back(h);
    }

    for (auto h : all) 
        DestroyEntryInternal(h);

    std::lock_guard lock(m_mutex);
    m_entries.clear();
    m_pathToHandle.clear();

}

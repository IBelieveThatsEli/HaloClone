#pragma once

#include "assets/handle.hpp"
#include "assets/mesh.hpp"

#include <atomic>
#include <functional>
#include <memory>

namespace Assets
{   
    using MeshHandle = Handle<Mesh>;

    class MeshLibrary 
    {
        public:
            static MeshLibrary& GetInstance();

            using MeshPtr = std::shared_ptr<Mesh>;

            using LoaderFunc = std::function<Mesh(std::string_view path)>;

            using GPUUploadFunc = std::function<void(MeshHandle, const Mesh&)>;
            using GPUDestroyFunc = std::function<void(MeshHandle)>;

            MeshLibrary();
            ~MeshLibrary();

            MeshLibrary(const MeshLibrary&) = delete;
            MeshLibrary& operator=(const MeshLibrary&) = delete;

            void SetLoader(LoaderFunc loader);

            void SetGPUUploadCallback(GPUUploadFunc uploadCb);
            void SetGPUDestroyCallback(GPUDestroyFunc destroyCb);

            MeshHandle LoadMesh(std::string_view path);

            MeshHandle GetHandleForPath(std::string_view path) const;

            MeshPtr Get(MeshHandle handle) const;

            void Release(MeshHandle handle);

            bool Exists(MeshHandle handle) const;

            void ClearUnused();

            void ClearAll();

        private:
            struct Entry 
            {
                MeshPtr mesh;
                u32 refCount = 0;
                std::string_view path;
            };

            MeshHandle CreateHandle();
            void DestroyEntryInternal(MeshHandle handle);

        private:
            mutable std::mutex m_mutex;

            std::unordered_map<std::string_view, MeshHandle> m_pathToHandle;
            std::unordered_map<MeshHandle, Entry> m_entries;

            std::atomic<u32> m_nextId;

            LoaderFunc      m_loader        = nullptr;
            GPUUploadFunc   m_gpuUpload     = nullptr;
            GPUDestroyFunc  m_gpuDestroy    = nullptr;
    };

} // namespace Assets

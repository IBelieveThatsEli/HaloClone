#pragma once

#include "utils/types.hpp"

namespace Assets
{
    template<typename T>
    struct MeshHandle
    {
        u32 id = 0;
        
        bool operator==(const MeshHandle& other) const 
        {
            return id == other.id;
        }

        MeshHandle& operator=(const MeshHandle& other)
        {
            if (this != &other)
                id = other.id;
            return *this;
        }

        explicit operator bool() const { return id != 0; }
    };
} // Assets

#include <functional>
namespace std 
{
    template<typename T>
    struct hash<Assets::MeshHandle<T>> 
    {
        size_t operator()(const Assets::MeshHandle<T>& h) const noexcept 
        {
            return std::hash<uint64_t>()(h.id);
        }
    };
}


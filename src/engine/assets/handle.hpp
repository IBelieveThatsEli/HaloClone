#pragma once

#include "utils/types.hpp"

namespace Assets
{
    template<typename T>
    struct Handle
    {
        u32 id = 0;
        
        bool operator==(const Handle& other) const 
        {
            return id == other.id;
        }

        Handle& operator=(const Handle& other)
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
    struct hash<Assets::Handle<T>> 
    {
        size_t operator()(const Assets::Handle<T>& h) const noexcept 
        {
            return std::hash<uint64_t>()(h.id);
        }
    };
}


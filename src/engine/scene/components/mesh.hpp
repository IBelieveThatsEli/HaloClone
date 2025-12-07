#pragma once

#include "utils/types.hpp"
#include "assets/handle.hpp"
#include "assets/mesh.hpp"
#include <string_view>

namespace Scene::Components
{
    struct Mesh
    {
        Assets::Handle<Assets::Mesh> mesh {};
        i32 submeshIndex;
        u32 materialID  = 0;
        std::string_view name;
    };
} // Scene::Components

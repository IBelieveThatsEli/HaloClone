#pragma once

#include "core/utils/types.hpp"

namespace Scene::Components
{
    struct Mesh
    {
        u32 meshID = 0;
        i32 submeshIndex = 0;
        u32 materialID  = 0;
    };
} // Scene::Components

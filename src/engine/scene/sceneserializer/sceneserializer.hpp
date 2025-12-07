#pragma once

#include <string_view>

namespace Scene
{
    class Scene;

    class SceneSerializer
    {
        public:
            [[nodiscard]] static bool Deserialize(Scene& scene, std::string_view path);
    };
} // Scene

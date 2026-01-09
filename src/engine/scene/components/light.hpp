#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>

#include "core/utils/types.hpp"

namespace Scene::Components
{
    enum class LightType
    {
        Directional, Point, Spot
    };

    struct Light
    {
        LightType type = LightType::Point;

        glm::vec3 color { 1.f, 1.f, 1.f };
        f32 intensity = 1.f;

        f32 radius = 10.f;

        f32 innerCutOff = glm::radians(15.f);
        f32 outerCutOff = glm::radians(25.f);
    };
} // Scene::Components

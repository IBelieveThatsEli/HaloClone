#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Scene::Components
{
    struct Transform
    {
        glm::vec3 position  { 0.f, 0.f, 0.f };
        glm::quat rotation  { 1.f, 0.f, 0.f, 0.f };
        glm::vec3 scale     { 1.f, 1.f, 1.f };

        glm::mat4 GatMatrix() const 
        {
            glm::mat4 t = glm::translate(glm::mat4(1.f), position);
            glm::mat4 r = glm::mat4_cast(rotation);
            glm::mat4 s = glm::scale(glm::mat4(1.f), scale);

            return t * r * s;
        };
    };
} // Scene::Components

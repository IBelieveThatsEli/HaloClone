#pragma once

#include "utils/types.hpp"

#define GLM_ENABLE_EXPERIMENTAL 1

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Scene::Components
{
    enum class CameraProjection
    {
        Perspective, Orthographic
    };

    struct Camera
    {
        CameraProjection projection = CameraProjection::Perspective;

        f32 fov         = 60.f;
        f32 nearPlane   = 0.1f;
        f32 farPlane    = 500.f;

        f32 orthoSize   = 10.f;

        glm::mat4 projectionMatrix {1.f};

        void RecalculateProjection(f32 aspectRatio)
        {
            if (projection == CameraProjection::Perspective)
            {
                projectionMatrix = glm::perspective(
                        glm::radians(fov),
                        aspectRatio,
                        nearPlane,
                        farPlane
                );
            }
            else
            {
                f32 half = orthoSize * 0.5f;

                projectionMatrix = glm::ortho(
                        -half * aspectRatio, half * aspectRatio,
                        -half, half,
                        nearPlane,
                        farPlane
                );
            }
        }

        glm::mat4 GetViewMatrix(const glm::vec3& position, const glm::quat& rotation) const
        {
            glm::vec3 forward = glm::rotate(rotation, glm::vec3(0, 0, -1));
            glm::vec3 up      = glm::rotate(rotation, glm::vec3(0, 1,  0));

            return glm::lookAt(position, position + forward, up);
        }
    };
} // Scene::Components

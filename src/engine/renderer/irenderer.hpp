#include "scene/scene.hpp"

namespace Renderer
{
    class IRenderer
    {
        public:
            virtual ~IRenderer() = default;

            virtual void SetScene(Scene::Scene& scene) = 0;
            virtual void Render() = 0;
    };
} // Renderer

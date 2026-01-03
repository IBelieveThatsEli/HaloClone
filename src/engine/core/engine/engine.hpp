#pragma once

#include "utils/types.hpp"
#include "core/api/api.hpp"

#include <memory>

class IRenderer;

namespace Scene
{
    class Scene;
}

namespace Core
{
    class Engine
    {
        public:
            Engine(const Core::GraphicsAPI& api);
            ~Engine();
           
            void SetGraphicsAPI(const Core::GraphicsAPI& api);

            void Update(f32 dt);

            void SetScene(std::shared_ptr<Scene::Scene> scene);

        private:
            Core::GraphicsAPI m_graphicsAPI;

            std::unique_ptr<IRenderer> m_renderer;

            std::shared_ptr<Scene::Scene> m_activeScene;

    };
} // Core

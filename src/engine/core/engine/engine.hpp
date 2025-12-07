#pragma once

#include "utils/types.hpp"
#include "core/api/api.hpp"

#include <memory>

namespace Scene
{
    class Scene;
}

namespace Core
{
    class Engine
    {
        public:
            Engine(Core::GraphicsAPI);
            ~Engine();
            
            void Update(f32 dt);

            void SetScene(std::shared_ptr<Scene::Scene> scene);

        private:
            Core::GraphicsAPI m_graphicsAPI;
            std::shared_ptr<Scene::Scene> m_activeScene;

    };
} // Core

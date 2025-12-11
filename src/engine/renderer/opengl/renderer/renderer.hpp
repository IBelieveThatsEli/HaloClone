#pragma once

#include "renderer/irenderer.hpp"

namespace Renderer::OpenGL
{
    class Renderer : public IRenderer
    {
        public:
            Renderer();
            ~Renderer() override;

            void SetScene(Scene::Scene& scene) override;
            void Render() override;

        private:
    };
};

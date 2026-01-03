#pragma once

#include <memory>

#include "platform/manager/manager.hpp"

namespace Core 
{
    class Engine;
}

namespace Engine
{
    class Application
    {
        public:
            Application(
                    const Core::GraphicsAPI&& = Core::GraphicsAPI::OpenGL, 
                    const Core::WindowAPI&&   = Core::WindowAPI::GLFW
            );
            ~Application();

            void ChangeWindowAPI(const Core::WindowAPI&& api);
            void ChangeGraphicsAPI(const Core::GraphicsAPI&& api);

            void LoadScene(std::string_view path);

            void Run();

        private:
            Platform::Manager m_platformManager;

            std::unique_ptr<Core::Engine> m_engine;
    };
} // Engine

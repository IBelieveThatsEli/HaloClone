#pragma once

#include <memory>

//#include "core/api/api.hpp"
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
                    Core::GraphicsAPI = Core::GraphicsAPI::OpenGL, 
                    Core::WindowAPI   = Core::WindowAPI::GLFW
            );
            ~Application();

            void LoadScene(std::string_view path);

            void Run();

        private:
            Platform::Manager m_platformManager;
            std::unique_ptr<Core::Engine> m_engine;
    };
} // Engine

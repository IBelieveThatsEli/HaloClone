#pragma once

#include "core/api/api.hpp"

#include "platform/basewindow/basewindow.hpp"
#include "platform/ieventbridge/ieventbridge.hpp"

#include <memory>

namespace Platform
{
    class Manager final
    {
        public:
            void Create(
                const Core::WindowAPI& api, 
                const BaseWindow::Properties& props
            );

            void ChangeGraphicsAPI(const Core::GraphicsAPI& api);

            void Update();

            [[nodiscard]] BaseWindow* GetWindow() noexcept { return m_window.get(); }

            [[nodiscard]] const Core::WindowAPI& GetAPI() const noexcept { return m_api; }

        private:
            Core::WindowAPI m_api;
            std::unique_ptr<BaseWindow> m_window;
            std::unique_ptr<IEventBridge> m_eventBridge;
    };
} // Platform

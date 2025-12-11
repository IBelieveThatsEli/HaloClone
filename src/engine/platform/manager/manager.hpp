#pragma once

#include "core/api/api.hpp"
#include "platform/basewindow/basewindow.hpp"

#include <memory>

namespace Platform
{
    class Manager
    {
        public:
            void Create(Core::WindowAPI api, Core::BaseWindow::Properties props);

            [[nodiscard]] Core::BaseWindow* GetWindow() noexcept { return m_window.get(); }

            [[nodiscard]] const Core::WindowAPI& GetAPI() const noexcept { return m_api; }

        private:
            Core::WindowAPI m_api;
            std::unique_ptr<Core::BaseWindow> m_window;
    };
} // Platform

#pragma once

#include "core/api/api.hpp"
#include "core/utils/types.hpp"

#include "platform/basewindow/basewindow.hpp"
#include "platform/ieventbridge/ieventbridge.hpp"

#include <memory>
#include <unordered_map>

namespace Platform
{
    // class Manager final
    // {
    //     public:
    //         void Create(
    //             const Core::WindowAPI& api, 
    //             const BaseWindow::Properties& props
    //         );

    //         void ChangeGraphicsAPI(const Core::GraphicsAPI& api);

    //         void Update();

    //         [[nodiscard]] BaseWindow* GetWindow() noexcept { return m_window.get(); }

    //         [[nodiscard]] const Core::WindowAPI& GetAPI() const noexcept { return m_api; }

    //     private:
    //         Core::WindowAPI m_api;
    //         std::unique_ptr<BaseWindow> m_window = nullptr;
    //         std::unique_ptr<IEventBridge> m_eventBridge = nullptr;
    // };

    typedef i32 WindowID;

    class Manager final
    {
        public:
            WindowID CreateWindow(const BaseWindow::Properties& properties);
            void DestoryWindow(WindowID id);

            void Update();

            [[nodiscard]] BaseWindow* GetWindow(WindowID id);
        
        private:
            std::unordered_map<WindowID, std::unique_ptr<BaseWindow>> m_windows;
            WindowID m_nextID = 1;
    }
} // Platform

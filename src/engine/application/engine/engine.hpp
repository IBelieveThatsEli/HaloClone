/**
 * @file    engine.hpp
 * @author  EMP "Ekam"
 * @brief   Declares the Engine runtime object.
 *
 * The Engine object represents the core runtime coordinator of the engine.
 * It owns and manages long-lived runtime systems such as the Platform and
 * Renderer managers, and exposes a unified update interface for driving
 * engine execution.
 *
 * The Engine is constructed once per application lifetime and is accessible
 * globally through a static instance accessor for convenience.
 * High-level application flow, including shutdown handling, is delegated
 * to the Application subsystem.
 * 
 * @date    2026
 */

#pragma once

#include "platform/manager/manager.hpp"

#include "core/utils/types.hpp"
#include "core/api/api.hpp"

#include <memory>

/**
 * @class Engine
 * @brief Central runtime coordinator for engine subsystems.
 * 
 * The Engine is responsible for initializing, owning, and updating
 * core runtime systems, including the Platform manager and Renderer manager.
 * It provides an update interface used by the Application to advance
 * engine execution each frame.
 *
 * The Engine does not control application lifetime directly.
 * Instead, it exposes shutdown request state which is queried and handled
 * by the Application subsystem.
 *
 * The Engine is instantiated once and accessed via a static instance
 * to simplify access across subsystems.
 * 
 */

class Engine final
{
    public:
        static Engine* GetInstance();

        ~Engine();

        [[nodiscard]] bool IsShutdownRequested() const noexcept { return m_shutdownRequest; }

        [[nodiscard]] Platform::Manager* GetPlatformManager() noexcept;

        void Update(f32 dt);

    private:
        Engine();

        std::unique_ptr<Platform::Manager> m_platformManager { nullptr };
        //std::unique_ptr<IRenderer> m_renderer { nullptr };

        bool m_shutdownRequest { false };
};

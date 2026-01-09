/**
 * @file    application.hpp
 * @author  EMP "Ekam"
 * @brief   Declares the Application object for the Application subsystem.
 * 
 * The Application object acts as the top-level coordinator of the runtime.
 * It is responsible for constructing and configuring high-level runtime objects,
 * initiating the main execution loop, and managing application lifetime and shutdown.
 *
 * The Application subsystem does not implement domain-specific engine logic.
 * Instead, it delegates responsibilities to dedicated engine subsystems such as
 * the Engine runtime, Platform manager, and supporting Core utilities.
 * 
 * @date    2026
 */

#pragma once

/**
 * @class Application
 * @brief High-level engine orchestrator and execution entry point.
 * 
 * Acts as the top-level runtime coordinator of the engine.
 *
 * The Application is responsible for:
 * - Constructing and wiring runtime objects (Engine, Platform, etc.)
 * - Driving the main loop
 * - Managing application startup and shutdown
 *
 * The Application does not own or implement rendering, input, or platform logic.
 * It coordinates subsystem interaction and enforces high-level execution flow.
 * 
 */

class Application final
{
    public:
        Application () = default;
        ~Application() = default;

        void Run    ();
};


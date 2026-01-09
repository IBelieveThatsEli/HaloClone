#include "application.hpp"

#include "engine/engine.hpp"

#include "core/time/time.hpp"

void Application::Run()
{
    Core::Time time;

    Engine *p_eng = Engine::GetInstance();

    while (!p_eng->IsShutdownRequested())
    {
        time.Tick();

        p_eng->Update(time.GetDeltaSeconds());
    }    
}

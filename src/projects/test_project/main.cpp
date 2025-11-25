#include "core/window/basewindow.hpp"
#include "input/manager.hpp"
#include "input/types/key.hpp"
#include "input/types/mousebutton.hpp"
#include "platform/glfw/window.hpp"
#include "core/events/eventbus.hpp"
#include "platform/glfw/eventbridge.hpp"



#include <GLFW/glfw3.h>
#include <initializer_list>
#include <print>
#include <exception>

#include <SDL3/SDL.h>
#include "platform/sdl3/window.hpp"

int main()
{
    try
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD) == false) {
            std::fprintf(stderr, "SDL_Init failed: {%s}\n", SDL_GetError());
            return -1;
        }

        Core::EventBus::GetInstance()
            .AddFramebufferListener([](i32 w, i32 h) {
                    std::print("{}x{}\n", w, h);
                });

        Core::BaseWindow::Properties properties{};

        SDL3::Window window(properties);

        Input::Manager man;
        man.EnableKeyboard(std::make_unique<Input::Keyboard>(std::initializer_list{Input::Key::Escape, Input::Key::F}));
        man.EnableMouse(std::make_unique<Input::Mouse>(std::initializer_list{Input::MouseButton::Left}));

        while (window.IsOpen())
        {
            window.PollEvents();

            if (auto keyboard = man.GetKeyboard(); keyboard)
            {
                if (keyboard->IsButtonDown(Input::Key::Escape))
                    window.Close();
            }

            if (auto mouse = man.GetMouse(); mouse)
            {
                static f64 x = 0.0;
                static f64 y = 0.0;

                if (mouse->GetX() != x || mouse->GetY() != y)
                {
                    x = mouse->GetX();
                    y = mouse->GetY();

                    std::print("{}x{}\n", x, y);
                }
            }

            if (auto gamepad = man.GetGamepad(); gamepad)
            {
                if (gamepad->buttons.IsButtonDown(Input::GamepadButton::A))
                    std::print("A\n");
            }

            man.Update(0);
        }

        SDL_Quit();
        /*glfwInit();

        Core::BaseWindow::Properties properties {};
        GLFW::Window window(properties);

        for (auto& func : window.GetFramebufferCallbacks()) 
            Core::EventBus::GetInstance()
                .AddFramebufferListener(
                        [func](i32 x, i32 y) { 
                            func(x, y); 
                        }
                );

        Core::EventBus::GetInstance()
            .AddFramebufferListener(
                    [](i32 x, i32 y) {
                        std::print("{}x{}\n", x, y);
                    }
            );

        Input::Manager man;
        man.EnableKeyboard(std::make_unique<Input::Keyboard>(std::initializer_list{Input::Key::Escape}));
        man.EnableMouse(std::make_unique<Input::Mouse>(std::initializer_list{Input::MouseButton::Left}));

        GLFW::EventBridge eventbridge;
        eventbridge.SetupCallbacks(window.GetHandle());

        while (window.IsOpen())
        {
            window.PollEvents();

            if (man.GetMouse()->IsButtonDown(Input::MouseButton::Left))
                std::print("Left Mouse Button\n");

            if (auto res = man.GetGamepad(); res && res->buttons.IsButtonDown(Input::GamepadButton::A))
                std::print("A\n");

            if (auto res = man.GetKeyboard(); res && res->IsButtonDown(Input::Key::Escape))
            {
                std::print("escape\n");
                window.Close();
            }

            man.Update(0);

            eventbridge.UpdateGamepads();
        }*/
    }
    catch (std::exception& e)
    {
        std::fprintf(stderr, "{%s}\n", e.what());
        return 1;
    }
    return 0;
}

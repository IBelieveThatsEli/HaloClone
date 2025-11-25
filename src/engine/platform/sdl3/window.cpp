#include "window.hpp"
#include "platform/sdl3/eventbridge.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <print>
#include <stdexcept>

using namespace SDL3;

Window::Window(Properties& properties)
    : BaseWindow(properties)
{
    u32 flags = 0;

    if (m_properties.resizable)
        flags |= SDL_WINDOW_RESIZABLE;

    if (!m_properties.visible)
        flags |= SDL_WINDOW_HIDDEN;

    if (m_properties.floating)
        flags |= SDL_WINDOW_ALWAYS_ON_TOP;

    if (m_properties.transparent)
        flags |= SDL_WINDOW_TRANSPARENT;

    if (m_properties.scaleToMonitor)
        flags |= SDL_WINDOW_HIGH_PIXEL_DENSITY;

    if (auto res = SDL_CreateWindow(
                m_properties.title.data(),
                m_properties.width, m_properties.height,
                flags);
            res)
        m_handle = res;
    else
        throw std::runtime_error("Failed to create SDL3::Window::Handle");

    SDL_SetWindowKeyboardGrab(m_handle, m_properties.focused);

    if (m_properties.iconify)
        SDL_MinimizeWindow(m_handle);

    SetWindowMode(m_properties.mode);

    SetVSync(m_properties.vsync);
}

Window::~Window()
{
    if (m_handle)
    {
        SDL_DestroyWindow(m_handle);
        m_handle = nullptr;
    }
}

void Window::PollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        EventBridge::ProcessEvent(event);
    }
}

void Window::SwapBuffers()
{
    SDL_GL_SwapWindow(m_handle);
}

bool Window::IsOpen() const
{
    return m_isOpen;
}

void Window::Close()
{
    m_isOpen = false;
}

void Window::SetWidth(i32 width)
{
    m_properties.width = width;

    SDL_SetWindowSize(m_handle, m_properties.width, m_properties.height);
}

void Window::SetHeight(i32 height)
{
    m_properties.height = height;

    SDL_SetWindowSize(m_handle, m_properties.width, m_properties.height);
}

void Window::SetTitle(std::string_view title)
{
    m_properties.title = title;
    SDL_SetWindowTitle(m_handle, m_properties.title.data());
}

void Window::SetResizable(bool flag)
{
    m_properties.resizable = flag;
    SDL_SetWindowResizable(m_handle, m_properties.resizable);
}
void Window::SetVisible(bool flag)
{
    m_properties.visible = flag;
    if(m_properties.visible)
        SDL_ShowWindow(m_handle);
    else
        SDL_HideWindow(m_handle);
}
void Window::SetFocused(bool flag)
{
    m_properties.focused = flag;
    SDL_SetWindowFocusable(m_handle, m_properties.focused);
}
void Window::SetIconified(bool flag)
{
    m_properties.iconify = flag;
    if (m_properties.iconify)
        SDL_MinimizeWindow(m_handle);
    else
        SDL_MaximizeWindow(m_handle);
}
void Window::SetFloating(bool flag)
{
    m_properties.floating = flag;
    SDL_SetWindowAlwaysOnTop(m_handle, m_properties.floating);
}
void Window::SetScaleToMonitor(bool flag)
{
    m_properties.scaleToMonitor = flag;

    // TODO
}
void Window::SetTransparent(bool flag)
{
    m_properties.transparent = flag;
    
    // TODO
}
void Window::SetVSync(bool flag)
{
    m_properties.vsync = flag;
    SDL_SetWindowSurfaceVSync(m_handle, m_properties.vsync ? 1 : 0);
}
void Window::SetWindowMode(Mode mode)
{
    int width  = m_properties.width;
    int height = m_properties.height;

    SDL_RestoreWindow(m_handle);

    switch (mode)
    {
        case Window::Mode::Windowed:
            SDL_SetWindowFullscreen(m_handle, 0); // remove fullscreen
            SDL_SetWindowBordered(m_handle, true);
            SDL_SetWindowSize(m_handle, width, height);
            break;

        case Window::Mode::BorderlessWindow:
            SDL_SetWindowFullscreen(m_handle, 0);
            SDL_SetWindowBordered(m_handle, false);
            SDL_SetWindowSize(m_handle, width, height);
            break;

        case Window::Mode::Fullscreen:
            SDL_SetWindowFullscreen(m_handle, SDL_WINDOW_FULLSCREEN);
            break;

        case Window::Mode::FullscreenBorderless:
            SDL_SetWindowBordered(m_handle, false);
            SDL_SetWindowFullscreen(m_handle, SDL_WINDOW_FULLSCREEN);
            break;
    }
}

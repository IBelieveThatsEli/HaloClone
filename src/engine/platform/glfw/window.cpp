#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <volk.h>

#include <stdexcept>

using namespace GLFW;

static i32 ConvertToGLFWBoolean(bool flag) { return flag ? GLFW_TRUE : GLFW_FALSE; }

Window::Window(const Properties& properties)
    : BaseWindow(properties) 
{
   CreateWindow(); 
}

Window::~Window()
{
    DestroyWindow();
    glfwTerminate();
}

void Window::CreateWindow()
{
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize glfw");

    glfwWindowHint(GLFW_RESIZABLE,                m_properties.resizable       ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE,                  m_properties.visible         ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUSED,                  m_properties.focused         ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_FLOATING,                 m_properties.floating        ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_ICONIFIED,                m_properties.iconify         ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR,         m_properties.scaleToMonitor  ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER,  m_properties.transparent     ? GLFW_TRUE : GLFW_FALSE);
   
    if (auto res = glfwCreateWindow(m_properties.width, m_properties.height, m_properties.title.data(), nullptr, nullptr);
        res)
        m_handle = res;
    else
        throw std::runtime_error("Failed to create GLFW::Window::Handle");

    glfwSetWindowUserPointer(m_handle, this);

    SetVSync(m_properties.vsync);
    SetWindowMode(m_properties.mode);

    if (m_properties.graphicsAPI == Core::GraphicsAPI::OpenGL)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_properties.glMajorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_properties.glMinorVersion);

        glfwMakeContextCurrent(m_handle);
    }
}

void Window::DestroyWindow()
{
    if (m_handle)
    {
        glfwDestroyWindow(m_handle);
        m_handle = nullptr;
    }
}

bool Window::IsOpen() const
{
    return !glfwWindowShouldClose(m_handle);
}

void Window::Close()
{
    glfwSetWindowShouldClose(m_handle, GLFW_TRUE);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_handle);
}

void Window::SetWidth (i32 width)
{
    if (width < 0)
        return;

    m_properties.width = width;

    glfwSetWindowSize(m_handle, m_properties.width, m_properties.height);
}

void Window::SetHeight(i32 height)
{
    if (height < 0)
        return;

    m_properties.height = height;

    glfwSetWindowSize(m_handle, m_properties.width, m_properties.height);
}

void Window::SetTitle (std::string_view title)
{
    m_properties.title = title;

    glfwSetWindowTitle(m_handle, m_properties.title.data());
}

void Window::ChangeGraphicsAPI(const Core::GraphicsAPI& api)
{
    m_properties.graphicsAPI = api;

    DestroyWindow();
    CreateWindow();
}

void Window::SetResizable(bool flag)
{
    m_properties.resizable = flag;

    glfwSetWindowAttrib(m_handle, GLFW_RESIZABLE, ConvertToGLFWBoolean(m_properties.resizable));
}

void Window::SetVisible(bool flag)
{
    m_properties.visible = flag;

    glfwSetWindowAttrib(m_handle, GLFW_VISIBLE, ConvertToGLFWBoolean(m_properties.visible));
}

void Window::SetFocused(bool flag)
{
    m_properties.focused = flag;

    glfwSetWindowAttrib(m_handle, GLFW_FOCUSED, ConvertToGLFWBoolean(m_properties.focused));
}

void Window::SetIconified(bool flag)
{
    m_properties.iconify = flag;

    glfwSetWindowAttrib(m_handle, GLFW_ICONIFIED, ConvertToGLFWBoolean(m_properties.iconify));
}

void Window::SetFloating(bool flag)
{
    m_properties.floating = flag;

    glfwSetWindowAttrib(m_handle, GLFW_FLOATING, ConvertToGLFWBoolean(m_properties.floating));
}

void Window::SetScaleToMonitor(bool flag)
{
    m_properties.scaleToMonitor = flag;

    glfwSetWindowAttrib(m_handle, GLFW_SCALE_TO_MONITOR, ConvertToGLFWBoolean(m_properties.scaleToMonitor));
}

void Window::SetTransparent(bool flag)
{
    m_properties.transparent = flag;

    glfwSetWindowAttrib(m_handle, GLFW_TRANSPARENT_FRAMEBUFFER, ConvertToGLFWBoolean(m_properties.transparent));
}

void Window::SetVSync(bool flag)
{
    m_properties.vsync = flag;

    glfwSwapInterval(m_properties.vsync ? 1 : 0);
}

void Window::SetWindowMode(Window::Mode mode)
{
    const GLFWvidmode*  m           = glfwGetVideoMode(glfwGetPrimaryMonitor());
    GLFWmonitor*        monitor     = nullptr;
    i32                 width       = 0;
    i32                 height      = 0;
    bool                decorated   = true;

    switch (mode)
    {
        case Window::Mode::Windowed:
            monitor             = nullptr;
            width               = m_properties.prevWidth;
            height              = m_properties.prevHeight;
            decorated           = true;
            break;

        case Window::Mode::BorderlessWindow:
            monitor             = nullptr;
            width               = m_properties.width; //monitor resolution...
            height              = m_properties.height;
            decorated           = false;
            break;

        case Window::Mode::Fullscreen:
            width               = m->width;
            height              = m->height;
            decorated           = true;
            break;

        case Window::Mode::FullscreenBorderless:
            monitor             = glfwGetPrimaryMonitor();
            decorated           = false;
            break;
    }

    glfwSetWindowAttrib(m_handle, GLFW_DECORATED, decorated ? GLFW_TRUE : GLFW_FALSE);
    glfwSetWindowMonitor(m_handle, monitor, 0, 0, width, height, 0);

    if (mode == Window::Mode::Windowed || mode == Window::Mode::BorderlessWindow)
        CenterWindow();
}

bool Window::InitGLAD() noexcept
{
    return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

bool Window::CreateVKWindowSurface() noexcept
{

}

void Window::CenterWindow()
{
    if (!m_handle) return;

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (!monitor) return;

    int monitorX, monitorY;
    glfwGetMonitorPos(monitor, &monitorX, &monitorY);

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (!mode) return;

    int windowWidth, windowHeight;
    glfwGetWindowSize(m_handle, &windowWidth, &windowHeight);

    int posX = monitorX + (mode->width - windowWidth) / 2;
    int posY = monitorY + (mode->height - windowHeight) / 2;

    glfwSetWindowPos(m_handle, posX, posY);
}

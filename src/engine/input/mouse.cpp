#include "mouse.hpp"

using namespace Input;

void Mouse::OnMoveEvent(f64 xpos, f64 ypos)
{
    static bool firstMouse = true;
    
    if (firstMouse)
    {
        m_lastX = xpos;
        m_lastY = ypos;
        firstMouse = false;
    }

    m_x = xpos;
    m_y = ypos;

    m_dx = m_x - m_lastX;
    m_dy = m_y - m_lastY;

    m_lastX = xpos;
    m_lastY = ypos;
}

void Mouse::OnScrollEvent(f64 xoffset, f64 yoffset)
{
    m_scrollX = xoffset;
    m_scrollY = yoffset;
}

void Mouse::Update()
{
    BaseButton::Update();

    m_dx = m_x - m_lastX;
    m_dy = m_y - m_lastY;

    m_lastX = m_x;
    m_lastY = m_y;

    m_scrollXFrame = m_scrollX;
    m_scrollYFrame = m_scrollY;

    m_scrollX = 0;
    m_scrollY = 0;
}

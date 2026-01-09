#pragma once

#include "basebutton.hpp"
#include "types/mousebutton.hpp"

namespace Input
{
    class Mouse final : public BaseButton<MouseButton>
    {
    public:
        Mouse(std::initializer_list<MouseButton> buttons)
            : BaseButton(buttons) {}

        void OnMoveEvent    (f64 xpos, f64 ypos);
        void OnScrollEvent  (f64 xoffset, f64 yoffset);

        void Update();

        [[nodiscard]] f64 GetX()        const noexcept { return m_x;  }
        [[nodiscard]] f64 GetY()        const noexcept { return m_y;  }
        [[nodiscard]] f64 GetDeltaX()   const noexcept { return m_dx; }
        [[nodiscard]] f64 GetDeltaY()   const noexcept { return m_dy; }

        [[nodiscard]] f64 GetScrollX()  const noexcept { return m_scrollX; }
        [[nodiscard]] f64 GetScrollY()  const noexcept { return m_scrollY; }

    private:
        f64 m_x            = 0.0;
        f64 m_y            = 0.0;
        f64 m_dx           = 0.0;     // per-frame delta
        f64 m_dy           = 0.0;
        f64 m_lastX        = 0.0;
        f64 m_lastY        = 0.0;

        f64 m_scrollX      = 0.0;
        f64 m_scrollY      = 0.0;
        f64 m_scrollXFrame = 0.0;
        f64 m_scrollYFrame = 0.0;
    };
} // Input

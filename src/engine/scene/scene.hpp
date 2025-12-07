#pragma once

#include <string_view>
#include <entt/entt.hpp>

#include "entity/entity.hpp"

namespace Scene
{
    class Scene
    {
        public:
            Scene(std::string_view name);
            ~Scene() = default;
  
            [[nodiscard]] Entity CreateEntity(std::string_view name = "Entity");

            [[nodiscard]] entt::registry&  GetRegistry()       noexcept { return m_registry; }
            [[nodiscard]] std::string_view GetName    () const noexcept { return m_name; }

        private:
            entt::registry m_registry;
            std::string_view m_name;
    };
} // Scene


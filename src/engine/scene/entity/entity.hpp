#pragma once

#include <entt/entt.hpp>

namespace Scene
{
    class Entity
    {
        public:
            Entity() = default;
            Entity(entt::entity handle, entt::registry* reg)
                : m_handle(handle), m_registry(reg) {}

            template<typename T, typename... Args>
            T& AddComponent(Args&&... args)
            {
                return m_registry->emplace<T>(m_handle, std::forward<Args>(args)...);
            }

            template<typename T>
            [[nodiscard]] bool HasComponent() const
            {
                return m_registry->all_of<T>(m_handle);
            }

        private:
            entt::entity m_handle { entt::null };
            entt::registry* m_registry { nullptr };
    };
} // Scene

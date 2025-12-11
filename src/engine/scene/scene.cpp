#include "scene.hpp"

#include "scene/components/tag.hpp"

namespace Scene
{
    Scene::Scene(std::string_view name)
        : m_name(name)
    {}

    Entity Scene::CreateEntity(std::string_view name)
    {
        entt::entity e = m_registry.create();
        Entity entity = Entity{ e, &m_registry };

        entity.AddComponent<Components::Tag>(name);

        return entity;
    }
} // Scene

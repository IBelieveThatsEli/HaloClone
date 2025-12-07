#include "scene.hpp"

#include "scene/components/tag.hpp"
#include "scene/components/transform.hpp"

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
        //entity.AddComponent<Components::Transform>();

        return entity;
    }
} // Scene

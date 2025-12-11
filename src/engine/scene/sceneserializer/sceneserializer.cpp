#include "sceneserializer.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <print>

#include "assets/meshlibrary.hpp"
#include "scene/scene.hpp"
#include "scene/components/transform.hpp"
#include "scene/components/camera.hpp"
#include "scene/components/mesh.hpp"

static glm::vec3 ReadVec3(const nlohmann::json& j)
{
    return glm::vec3(j[0], j[1], j[2]);
}

using namespace Scene;

bool SceneSerializer::Deserialize(Scene &scene, std::string_view path)
{
    std::ifstream file(path.data());

    if (!file.is_open())
    {
        std::print("File not found");
        return false;
    }

    nlohmann::json data;
    file >> data;

    if (!data.contains("entities"))
            return false;

    for (auto& entJson : data["entities"])
    {
        auto entity = scene.CreateEntity(entJson.value("name", "Entity"));

        auto& reg = scene.GetRegistry();

        auto& comps = entJson["components"];

        if (comps.contains("Transform"))
        {
            auto& j = comps["Transform"];
            auto& t = entity.AddComponent<Components::Transform>();

            if (j.contains("position")) t.position = ReadVec3(j["position"]);
            if (j.contains("rotation")) t.rotation = ReadVec3(j["rotation"]);
            if (j.contains("scale"))    t.scale    = ReadVec3(j["scale"]);
        }

        if (comps.contains("Camera"))
        {
            auto& j = comps["Camera"];
            auto& cam = entity.AddComponent<Components::Camera>();

            std::string proj = j.value("projection", "Perspective");
            cam.projection =
                (proj == "Orthographic")
                ? Components::CameraProjection::Orthographic
                : Components::CameraProjection::Perspective;

            cam.fov       = j.value("fov", cam.fov);
            cam.nearPlane = j.value("near", cam.nearPlane);
            cam.farPlane  = j.value("far", cam.farPlane);
        }

        if (comps.contains("Mesh"))
        {
            auto& j = comps["Mesh"];
            auto& mesh = entity.AddComponent<Components::Mesh>();

            std::string file = j["file"];
            i32 submesh = j.value("submesh", 0);

            u32 handleID = Assets::MeshLibrary::Get().LoadMesh(file);
            mesh.meshID = handleID; 
            mesh.submeshIndex = submesh;
        }
    }

    file.close();

    return true;
}

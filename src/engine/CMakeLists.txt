project(engine VERSION 0.0.1 LANGUAGES CXX)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(${PROJECT_NAME} STATIC ${SOURCES})

# link a single windowing api at a time.

if (ENGINE_USE_GLFW)
    target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
endif()
if (ENGINE_USE_SDL)
    target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3)
endif()

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        OpenGL::GL
        Vulkan::Vulkan
        glad
        volk
        nlohmann_json::nlohmann_json
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${nuklear_SOURCE_DIR}
        ${entt_SOURCE_DIR}/src
        ${tinygltf_SOURCE_DIR}
        ${glm_SOURCE_DIR}
)

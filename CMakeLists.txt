cmake_minimum_required(VERSION 3.25)
project(HaloClone VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS ON) 

find_package(OpenGL REQUIRED)
find_package(Vulkan REQUIRED)

include(FetchContent)

set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY    https://github.com/glfw/glfw.git
  GIT_TAG           3.4 
)

FetchContent_MakeAvailable(glfw)

set(SDL_TEST            OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES        OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL         OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL.git
    GIT_TAG         release-3.2.26
)

FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(
    nuklear
    GIT_REPOSITORY  https://github.com/Immediate-Mode-UI/Nuklear.git
    GIT_TAG         4.12.8 
)

FetchContent_MakeAvailable(nuklear)

FetchContent_Declare(
    volk
    GIT_REPOSITORY  https://github.com/zeux/volk.git
    GIT_TAG         1.4.304
)

set(VOLK_BUILD_TESTS  OFF CACHE BOOL "" FORCE)
set(VOLK_BUILD_DEMO   OFF CACHE BOOL "" FORCE)
set(VOLK_INSTALL      OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(volk)

FetchContent_Declare(
    glm
    GIT_REPOSITORY  https://github.com/g-truc/glm.git
    GIT_TAG         master 
)

set(GLM_BUILD_TESTS   OFF CACHE BOOL "" FORCE)
set(GLM_BUILD_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glm)

FetchContent_Declare(
    EnTT
    GIT_REPOSITORY  https://github.com/skypjack/entt.git
    GIT_TAG         v3.13.1
)

FetchContent_MakeAvailable(EnTT)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY  https://github.com/nlohmann/json.git
    GIT_TAG         v3.11.3
)

set(JSON_BuildTests      OFF CACHE INTERNAL "")
set(JSON_MultipleHeaders OFF CACHE INTERNAL "")
set(JSON_Install         OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(
    tinygltf
    GIT_REPOSITORY  https://github.com/syoyo/tinygltf.git
    GIT_TAG         v2.9.7
)

set(TINYGLTF_BUILD_LOADER_EXAMPLE OFF CACHE BOOL "" FORCE)
set(TINYGLTF_BUILD_LOADER_SAMPLE OFF CACHE BOOL "" FORCE)
set(TINYGLTF_BUILD_GL_EXAMPLE OFF CACHE BOOL "" FORCE)
set(TINYGLTF_BUILD_GLTF2MODEL OFF CACHE BOOL "" FORCE)
set(TINYGLTF_BUILD_OBJ_LOADER OFF CACHE BOOL "" FORCE)
set(TINYGLTF_BUILD_TESTS OFF CACHE BOOL "" FORCE)

# TinyGLTF normally bundles nlohmann JSON internally.
# You already fetch nlohmann/json, so let tinygltf use yours:
set(TINYGLTF_INSTALL OFF CACHE BOOL "" FORCE)
set(TINYGLTF_USE_EXTERNAL_JSON ON CACHE BOOL "" FORCE)

set(TINYGLTF_BUILD_LOADER_EXAMPLES  OFF CACHE BOOL "" FORCE)
set(TINYGLTF_BUILD_GL_EXAMPLES      OFF CACHE BOOL "" FORCE)
set(TINYGLTF_BUILD_GLTF_VIEWER      OFF CACHE BOOL "" FORCE)

set(TINYGLTF_HEADER_ONLY        ON CACHE BOOL "" FORCE)
set(TINYGLTF_ENABLE_LOADER_JSON ON CACHE BOOL "" FORCE)
set(TINYGLTF_USE_CPP14          ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(tinygltf)

add_library(glad STATIC "${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/src/glad.c")
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include)

add_subdirectory(src/engine)
add_subdirectory(src/projects/test_project)
add_subdirectory(src/projects/hello_triangle)

cmake_minimum_required(VERSION 3.25)
project(HaloClone VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS ON) 

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

#set(SDL_VIDEO_X11     ON CACHE BOOL "" FORCE)
#set(SDL_VIDEO_WAYLAND OFF CACHE BOOL "" FORCE)
#set(SDL_VIDEO_DIRECTFB OFF CACHE BOOL "" FORCE)
#set(SDL_VIDEO_RPI     OFF CACHE BOOL "" FORCE)
#set(SDL_VIDEO_COCOA   OFF CACHE BOOL "" FORCE)
#set(SDL_VIDEO_WAYLAND   OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL.git
    GIT_TAG         release-3.2.26
)

FetchContent_MakeAvailable(SDL3)

add_subdirectory(src/engine)
add_subdirectory(src/projects/test_project)

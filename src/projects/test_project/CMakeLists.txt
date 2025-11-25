project(test_project VERSION 0.0.1 LANGUAGES CXX)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        engine
)

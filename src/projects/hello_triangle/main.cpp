#include "application/application.hpp"

#include <cstdio>
#include <exception>

int main()
{
    try 
    {
        Engine::Application hello_triangle;
        hello_triangle.LoadScene("src/projects/hello_triangle/scenes/scene.json");
        hello_triangle.Run();
    } 
    catch (std::exception& e) 
    {
        std::fprintf(stderr, "{%s}\n", e.what());
        return -1;
    }

    return 0;
}

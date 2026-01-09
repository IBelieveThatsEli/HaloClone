#include "application/application.hpp"

#include <cstdio>
#include <exception>

int main()
{
    try 
    {
        Application hello_triangle;
        hello_triangle.Run();
    } 
    catch (std::exception& e) 
    {
        std::fprintf(stderr, "{%s}\n", e.what());
        return -1;
    }

    return 0;
}

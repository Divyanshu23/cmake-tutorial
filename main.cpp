#include<bits/stdc++.h>
#include<adder.hpp>
#include<GLFW/glfw3.h>
#include<OLASConfigure.h>

using namespace std;


float add(float a, float b);

int main(int argc, char* argv[])
{
    cout<<argv[0]<<" Version "<<OLAS_VERSION_MAJOR<<"."<<OLAS_VERSION_MINOR<<"\n";
    cout<<"Hello World\n";

    GLFWwindow* window;

    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    window = glfwCreateWindow( 300, 300, "Gears", NULL, NULL );
    if (!window)
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    while( !glfwWindowShouldClose(window) )
    {
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}
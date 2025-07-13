//
// Created by Carlo Baretta on 13/07/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <glad/Glad.h>
//Always include glfw AFTER glad
#include <GLFW/glfw3.h>


void resizeAdjustViewportCallback(GLFWwindow* window, int width, int height);


void glfwSetup() {
    constexpr int majorVersion = 4;
    constexpr int minorVersionMac = 1;
    constexpr int minorVersionRest = 6;

    //Initialise GLFW
    glfwInit();
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    //macOS: OpenGL 4.1, forward compatibility
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersionMac);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    //Other platforms: OpenGL 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersionRest);
#endif
}

GLFWwindow* createWindow() {
    constexpr char programTitle[] = "GraphicsEngine";
    constexpr int width = 800;
    constexpr int height = 600;
    constexpr int xPos = 0;
    constexpr int yPos = 0;

    GLFWwindow* window = glfwCreateWindow(width, height, programTitle, nullptr, nullptr);
    if (!window)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetFramebufferSizeCallback(window, resizeAdjustViewportCallback);


    glfwMakeContextCurrent(window);

    //Initialise GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        exit(EXIT_FAILURE);
    }

    //Create viewport
    /*
     Note: This can be made smaller than the actual window (GLFWwindow*),
     so that you can use for example native UI elements around the smaller viewport that renders the OpenGL graphics.
    */
    glViewport(xPos, yPos, width, height);

    return window;
}

void cleanupWindow(GLFWwindow* window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}



//GLFW callbacks. Prototypes of these functions are defined at the top of the file
//window seems to not be used, however to register the callback the window parameter is expected.
void resizeAdjustViewportCallback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height);
}
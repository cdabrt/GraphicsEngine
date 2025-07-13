//
// Created by Carlo Baretta on 13/07/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>



void resizeAdjustViewportCallback(GLFWwindow* window, int width, int height);



void glfwWindowSetup() {
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

GLFWwindow* createWindow(const int width, const int height) {
    constexpr char programTitle[] = "GraphicsEngine";

    GLFWwindow* window = glfwCreateWindow(width, height, programTitle, nullptr, nullptr);
    if (!window) {
        perror("Failed to create GLFW window");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetFramebufferSizeCallback(window, resizeAdjustViewportCallback);


    glfwMakeContextCurrent(window);

    return window;
}

void cleanupWindow(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}



//GLFW callbacks. Prototypes of these functions are defined at the top of the file
//window seems to not be used, however to register the callback the window parameter is expected.
void resizeAdjustViewportCallback(GLFWwindow* window, const int width, const int height) {
    glViewport(0, 0, width, height);
}
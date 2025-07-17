//
// Created by Carlo Baretta on 10/07/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <Window.h>
#include <GLFW/glfw3.h>
#include <WindowInputController.h>
#include <../include/RendererAPI/RendererFactory.h>
#include "../include/RendererAPI/Renderer.h"

int main() {
    constexpr int width = 800;
    constexpr int height = 600;
    constexpr int xPos = 0;
    constexpr int yPos = 0;

    constexpr bool drawWireframe = false;

    glfwWindowSetup();
    GLFWwindow* window = createWindow(width, height);

    struct Renderer *renderer = createRenderer(window, OPENGL);
    struct RendererInjector *rendererInjector = createRendererInjector(OPENGL);

    void *context = renderer->context;
    renderer->initialize(context, xPos, yPos, width, height);

    //TODO: REMOVE, FOR TESTING ONLY
    //Vertices are constructed as follows:
    //x, y, z; r, g, b
    constexpr float vertices[] = {
        0.0f,  0.6f, 0.0f,  1.0f, 0.0f, 0.0f,  //0: Top of roof
        0.5f,  0.2f, 0.0f,  0.8f, 0.5f, 0.2f,  //1: Right roof corner
       -0.5f,  0.2f, 0.0f,  0.8f, 0.5f, 0.2f,  //2: Left roof corner
        0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  //3: Bottom right wall
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  //4: Bottom left wall
        0.3f,  0.3f, 0.0f,  1.0f, 0.0f, 0.0f,  //5: Right bottom chimney
        0.2f,  0.3f, 0.0f,  0.0f, 1.0f, 0.0f,  //6: Left bottom chimney
        0.3f,  0.6f, 0.0f,  0.0f, 0.0f, 1.0f,  //7: Right top chimney
        0.2f,  0.6f, 0.0f,  0.5f, 0.5f, 0.5f,  //8: Left top chimney
   };

    const unsigned int indices[] = {
        //Roof
        0, 1, 2,
        //Walls
        3, 4, 1,
        4, 2, 1,
        //Chimney
        5, 6, 7,
        6, 8, 7,
    };

    rendererInjector->registerMesh(context, vertices, indices, sizeof(vertices), sizeof(indices));
    renderer->prepareRenderer(drawWireframe);

    //Main window render loop
    while (!glfwWindowShouldClose(window)) {
        //Input processing
        //TODO: Perhaps we can attach a callback to here, which can register callbacks for certain inputs
        //  Each renderer can do it for it's own thing or whatever. Have to think about that one carefully
        processWindowInput(window);

        //Rendering pipeline
        renderer->render(context);

        renderer->swapBuffers(renderer->context);
    }

    /*
     TODO: Perhaps this should be a Windows and Linux only thing. In Mac if you press the "x",
        it does not fully quit the program, just hides it in the background.
        Probably do not terminate the while loop on macOS.
    */
    cleanupWindow(window);

    renderer->kill(renderer->context);
    free(renderer);

    return EXIT_SUCCESS;
}

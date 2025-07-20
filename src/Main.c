//
// Created by Carlo Baretta on 10/07/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <_string.h>
#include <Window.h>
#include <WindowInputController.h>
#include <../include/RendererAPI/Renderer.h>
#include <../include/RendererAPI/Mesh.h>
#include <../include/RendererAPI/RendererFactory.h>
#include "Renderer/OpenGL/OpenGLHeaders.h"

int main() {
    const int width = 800;
    const int height = 600;
    const int xPos = 0;
    const int yPos = 0;

    const bool drawWireframe = false;

    glfwWindowSetup();
    GLFWwindow* window = createWindow(width, height);

    struct Renderer *renderer = createRenderer(window, OPENGL);
    struct RendererInjector *rendererInjector = createRendererInjector(OPENGL);

    void *context = renderer->context;
    renderer->initialize(context, xPos, yPos, width, height);

    //TODO: REMOVE, FOR TESTING ONLY
    //Vertices are constructed as follows:
    //x, y, z; r, g, b
    const float vertices[] = {
        //Positions         //Colours           //Texture coordinates
        -0.5f,  0.5f, 0.0f,  0.8f, 0.5f, 0.2f,   0.0f, 1.0f,
        0.5f,  0.5f, 0.0f,  0.8f, 0.5f, 0.2f,   1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
   };

    const unsigned int indices[] = {
        2, 3, 0,
        3, 1, 0,
    };

    struct Texture textures[] = {
        {
            strdup("../src/Renderer/OpenGL/Textures/House.png"),
            DIFFUSE,
            "diffuse",
            .id = 0,
            0
        }
    };

    struct Mesh mesh = {
        vertices,
        indices,
        sizeof(vertices),
        sizeof(indices),
        textures,
        sizeof(textures) / sizeof(textures[0]),
        };

    rendererInjector->registerMesh(context, &mesh);

    renderer->prepareRenderer(drawWireframe);

    //Main window render loop
    while (!glfwWindowShouldClose(window)) {
        //Input processing
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

    renderer->kill(renderer->context);
    free(renderer);

    return EXIT_SUCCESS;
}

//
// Created by Carlo Baretta on 10/07/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <Window.h>
#include <GLFW/glfw3.h>
#include <WindowInputController.h>
#include <Renderer/RendererFactory.h>
#include "Renderer/Renderer.h"

int main() {
    constexpr int width = 800;
    constexpr int height = 600;
    constexpr int xPos = 0;
    constexpr int yPos = 0;

    glfwWindowSetup();
    GLFWwindow* window = createWindow(width, height);

    struct Renderer *renderer = createRenderer(window, OPENGL);
    renderer->initialize(xPos, yPos, width, height);

    //Main window render loop
    while (!glfwWindowShouldClose(window)) {
        //Input processing
        //TODO: Perhaps we can attach a callback to here, which can register callbacks for certain inputs
        //  Each renderer can do it for it's own thing or whatever. Have to think about that one carefully
        processWindowInput(window);

        //Rendering pipeline
        renderer->render(window);

        renderer->swapBuffers(renderer->context);
    }

    /*
     TODO: Perhaps this should be a Windows and Linux only thing. In Mac if you press the "x",
        it does not fully quit the program, just hides it in the background.
        Probably do not terminate the while loop on macOS.
    */
    cleanupWindow(window);

    free(renderer->context);
    free(renderer);

    return EXIT_SUCCESS;
}

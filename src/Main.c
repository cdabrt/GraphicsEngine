//
// Created by Carlo Baretta on 10/07/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <Window.h>
#include <GLFW/glfw3.h>
#include <InputController.h>

int main()
{
    glfwSetup();

    GLFWwindow* window = createWindow();

    //Main window render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.4f, 0.5f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /*
     TODO: Perhaps this should be a Windows and Linux only thing. In Mac if you press the "x",
        it does not fully quit the program, just hides it in the background.
        Probably do not terminate the while loop on macOS.
    */
    cleanupWindow(window);

    return EXIT_SUCCESS;
}
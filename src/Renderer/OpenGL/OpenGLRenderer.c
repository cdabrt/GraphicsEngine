//
// Created by Carlo Baretta on 13/07/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <glad/Glad.h>
#include "OpenGLRenderer.h"

void openGLInitialize(const int xPos, const int yPos, const int width, const int height) {
    //Initialise GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD \n");
        exit(EXIT_FAILURE);
    }

    //Create viewport
    /*
     Note: This can be made smaller than the actual window (GLFWwindow*),
     so that you can use for example native UI elements around the smaller viewport that renders the OpenGL graphics.
    */
    glViewport(xPos, yPos, width, height);
}

//Poll events and swat front buffer with back buffers
void openGLRender (void *context) {
    struct OpenGLContext *openGLContext = (struct OpenGLContext *)context;
    glClearColor(0.4f, 0.5f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

//Poll events and swat front buffer with back buffers
void openGLSwapBuffers (void *context) {
    struct OpenGLContext *openGLContext = (struct OpenGLContext *)context;
    glfwPollEvents();
    glfwSwapBuffers(openGLContext->window);
}
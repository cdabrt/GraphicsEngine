//
// Created by Carlo Baretta on 13/07/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <glad/Glad.h>
#include "OpenGLRenderer.h"
#include <string.h>
#include <GLFW/glfw3.h>
#include "OpenGLContext.h"



void openGLRender (void *context, float vertices[]) {
    struct OpenGLContext *openGLContext = (struct OpenGLContext *)context;

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glUseProgram(openGLContext->activeShaderProgram);


    //TODO: Temporary background colour
    glClearColor(0.4f, 0.5f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}



void initializeBaseShaders(struct OpenGLContext *openGLContext) {
    constexpr char filePathBase[] = "../src/Renderer/OpenGL/Shaders/";
    char vertexFullPath[512];
    char fragmentFullPath[512];

    snprintf(vertexFullPath, sizeof(vertexFullPath), "%s%s", filePathBase, "Vertex/vertex_main.vert");
    snprintf(fragmentFullPath, sizeof(fragmentFullPath), "%s%s", filePathBase, "Fragment/fragment_main.frag");


    const GLuint shaderProgram = createShaderProgram(vertexFullPath, fragmentFullPath);
    addShaderProgram(openGLContext, shaderProgram);
    setActiveShaderProgram(openGLContext, shaderProgram);
}



void openGLInitialize(void *context, const int xPos, const int yPos, const int width, const int height) {
    struct OpenGLContext *openGLContext = (struct OpenGLContext *)context;

    //Initialise GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        perror("Failed to initialize GLAD \n");
        exit(EXIT_FAILURE);
    }

    //Create viewport
    /*
     Note: This can be made smaller than the actual window (GLFWwindow*),
     so that you can use for example native UI elements around the smaller viewport that renders the OpenGL graphics.
    */
    glViewport(xPos, yPos, width, height);

    initializeBaseShaders(openGLContext);
}



//Poll events and swap front buffer with back buffers
void openGLSwapBuffers (void *context) {
    struct OpenGLContext *openGLContext = (struct OpenGLContext *)context;
    glfwPollEvents();
    glfwSwapBuffers(openGLContext->window);
}



void openGLKill (void *context) {
    struct OpenGLContext *openGLContext = (struct OpenGLContext *)context;
    for (int i =0; i < openGLContext->shaderCount; i++) {
        const struct ShaderProgram shaderProgram = openGLContext->shaderPrograms[i];
        glDeleteProgram(shaderProgram.id);
    }
    openGLContext->shaderCount = 0;
    free(openGLContext->shaderPrograms);
    free(context);
}
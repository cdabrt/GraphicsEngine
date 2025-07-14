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



unsigned int openGLPrepareRender (const float *vertices, const float *indices,
    const long vertexDataSize, const long indicesDataSize, const bool drawWireframe) {
    if (drawWireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesDataSize, indices, GL_STATIC_DRAW); ;

    //Vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    //Colour position
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
        6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return VAO;
}



void openGLRender (void *context, const unsigned int VAO) {
    struct OpenGLContext *openGLContext = (struct OpenGLContext *)context;
    //TODO: Temporary background colour
    glClearColor(0.4f, 0.5f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint activeShaderProgram = openGLContext->activeShaderProgram;

    glUseProgram(activeShaderProgram);

    // //Rainbow colour
    // const float timeValue = glfwGetTime();
    // const int time = glGetUniformLocation(activeShaderProgram, "time");
    // glUniform1f(time, timeValue);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
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
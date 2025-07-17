//
// Created by Carlo Baretta on 13/07/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <glad/Glad.h>
#include "OpenGLRenderer.h"
#include <GLFW/glfw3.h>
#include "OpenGLContext.h"
#include "OpenGLMacros.h"
#include "ShaderCompiler/OpenGLInjector.h"


void initializeBaseShaders(struct OpenGLContext *openGLContext) {
    const char filePathBase[] = "../src/Renderer/OpenGL/Shaders/";
    char vertexFullPath[512];
    char fragmentFullPath[512];

    snprintf(vertexFullPath, sizeof(vertexFullPath), "%s%s", filePathBase, "Vertex/vertex_main.vert");
    snprintf(fragmentFullPath, sizeof(fragmentFullPath), "%s%s", filePathBase, "Fragment/fragment_main.frag");


    const GLuint shaderProgram = openGLCreateShaderProgram(vertexFullPath, fragmentFullPath);
    addShaderProgram(openGLContext, shaderProgram);
    openGLSetActiveShaderProgram(openGLContext, shaderProgram);
}



void openGLInitialize(void *context, const int xPos, const int yPos, const int width, const int height) {
    OPENGL_CTX;

    //Initialise GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        perror("Failed to initialize GLAD \n");
        exit(EXIT_FAILURE);
    }

    glViewport(xPos, yPos, width, height);

    initializeBaseShaders(openGLContext);
}



void openGLPrepareRender (const bool drawWireframe) {
    if (drawWireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

//TODO: See TODO of openGLRegisterMesh.
void openGLRender (void *context) {
    OPENGL_CTX;

    //TODO: Temporary background colour
    glClearColor(0.4f, 0.5f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    const GLuint activeShaderProgram = openGLContext->activeShaderProgram;

    glUseProgram(activeShaderProgram);

    size_t totalIndicesCount = 0;

    //TODO: Add frustum culling, other types of culling, etc
    if (openGLContext->vaoCount > 0) {
        for (int i = 0; i < openGLContext->vaoCount; i++) {
            const struct VAO vao = openGLContext->vaos[i];
            glBindVertexArray(vao.id);
            totalIndicesCount += vao.indicesCount;
        }
    }

    glDrawElements(GL_TRIANGLES, (GLsizei) totalIndicesCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}



//Poll events and swap front buffer with back buffers
void openGLSwapBuffers (void *context) {
    OPENGL_CTX;
    glfwPollEvents();
    glfwSwapBuffers(openGLContext->window);
}



void openGLKill (void *context) {
    OPENGL_CTX;

    for (size_t i =0; i < openGLContext->shaderCount; i++) {
        const struct ShaderProgram shaderProgram = openGLContext->shaderPrograms[i];
        glDeleteProgram(shaderProgram.id);
    }

    for (size_t i =0; i < openGLContext->vaoCount; i++) {
        const struct VAO vao = openGLContext->vaos[i];
        glDeleteVertexArrays(1, &vao.id);
    }

    openGLContext->shaderCount = 0;
    openGLContext->vaoCount = 0;
    free(openGLContext->shaderPrograms);
    free(openGLContext->vaos);
    free(openGLContext);
}
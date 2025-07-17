//
// Created by Carlo Baretta on 14/07/2025.
//

#include <stdlib.h>
#include "../OpenGLErrorHandling.h"
#include "glad/Glad.h"
#include "UtilFiles/ReadFile.h"
#include "../OpenGLContext.h"
#include "Renderer/OpenGL/OpenGLMacros.h"


unsigned int compileShader (char filePath[], const unsigned int shaderType) {
    const unsigned int shader = glCreateShader(shaderType);
    const int numberOfShaders = 1;
    char *shaderSource = readFile(filePath);

    //Attach shader source to the shader object and compile
    glShaderSource(shader, numberOfShaders, (const GLchar * const*) &shaderSource, nullptr);
    free(shaderSource);
    glCompileShader(shader);

    checkCompilationSuccess(shader);

    return shader;
}

unsigned int linkShaders (const unsigned int vertexShader, const unsigned int fragmentShader) {
    const unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    checkLinkingSuccess(shaderProgram);

    return shaderProgram;
}



/*
 Because we create the shader program in this function,
 this function can be exposed so external developers can add their own shaders
 */
unsigned int openGLCreateShaderProgram(char *vertexFilePath, char *fragmentFilePath) {
    const unsigned int vertexShader = compileShader(
        vertexFilePath,
        GL_VERTEX_SHADER
        );

    const unsigned int fragmentShader = compileShader(
    fragmentFilePath,
        GL_FRAGMENT_SHADER
        );

    const unsigned int shaderProgram = linkShaders(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

void openGLSetActiveShaderProgram(void *context, const unsigned long programId) {
    OPENGL_CTX;

    glUseProgram(programId);
    openGLContext->activeShaderProgram = programId;
}


//TODO: Register static mesh, put it into one big VBO and use glMultiDrawIndirect for frustum culling of the big static VBO.
//  The dynamic meshes still need to be frustum culled
//  Also look into instancing (trees, bullets, etc)
void openGLRegisterMesh(void *context, const float *vertices, const int *indices,
    const long vertexDataSize, const long indicesDataSize) {
    OPENGL_CTX;
    const int vertexAttribIndex = 0;
    const int vertexColourAttribIndex = 1;
    const int vertexBlockSize = 3;
    const int stride = 6;

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
    glVertexAttribPointer(vertexAttribIndex, vertexBlockSize, GL_FLOAT, GL_FALSE,
        stride * sizeof(float), nullptr);
    glEnableVertexAttribArray(vertexAttribIndex);

    //Colour position
    glVertexAttribPointer(vertexColourAttribIndex, vertexBlockSize, GL_FLOAT, GL_FALSE,
        stride * sizeof(float), (void*)(vertexBlockSize * sizeof(float)));
    glEnableVertexAttribArray(vertexColourAttribIndex);

    addVAO(openGLContext, VAO, indicesDataSize);
}
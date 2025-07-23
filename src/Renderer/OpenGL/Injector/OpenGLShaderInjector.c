//
// Created by Carlo Baretta on 14/07/2025.
//

#include <stdio.h>
#include "../include/RendererAPI/Mesh.h"
#include "Renderer/OpenGL/OpenGLErrorHandling.h"
#include "UtilFiles/ReadFile.h"
#include "Renderer/OpenGL/OpenGLContext.h"
#include "Renderer/OpenGL/OpenGLMacros.h"
#include <stb_image.h>
#include "Renderer/OpenGL/OpenGLHeaders.h"
#include "Renderer/OpenGL/Injector/OpenGLInjector.h"



unsigned int compileShader (char filePath[], const unsigned int shaderType) {
    const unsigned int shader = glCreateShader(shaderType);
    const int numberOfShaders = 1;
    char *shaderSource = readFile(filePath);
    if (!shaderSource) {
        fprintf(stderr, "Failed to read shader source: %s\n", filePath);
        exit(EXIT_FAILURE);
    }

    //Attach shader source to the shader object and compile
    glShaderSource(shader, numberOfShaders, (const GLchar * const*) &shaderSource, NULL);
    free(shaderSource);
    glCompileShader(shader);

    checkCompilationSuccess(shader);

    return shader;
}

unsigned int linkShaders (const unsigned int vertexShader, const unsigned int geometryShader, const unsigned int fragmentShader) {
    const unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    if (geometryShader != GL_NONE) {
        glAttachShader(shaderProgram, geometryShader);
    }
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    checkLinkingSuccess(shaderProgram);

    return shaderProgram;
}

/*
 Because we create the shader program in this function,
 this function can be exposed so external developers can add their own shaders
 */
unsigned int openGLCreateShaderProgram(char *vertexFilePath, char *geometryFullPath, char *fragmentFilePath) {
    const unsigned int vertexShader = compileShader(
        vertexFilePath,
        GL_VERTEX_SHADER
        );

    const unsigned int fragmentShader = compileShader(
    fragmentFilePath,
        GL_FRAGMENT_SHADER
        );

    unsigned int geometryShader = GL_NONE;
    if (geometryFullPath[0] != '\0') {
        geometryShader = compileShader(
            geometryFullPath,
            GL_GEOMETRY_SHADER
            );
    }

    const unsigned int shaderProgram = linkShaders(vertexShader, geometryShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if (geometryShader != GL_NONE) glDeleteShader(geometryShader);

    return shaderProgram;
}

void openGLSetActiveShaderProgram(void *context, const unsigned long programId) {
    OPENGL_CTX;
    glUseProgram(programId);
    openGLContext->activeShaderProgram = programId;
}
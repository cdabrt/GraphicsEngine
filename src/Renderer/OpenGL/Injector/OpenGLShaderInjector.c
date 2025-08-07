//
// Created by Carlo Baretta on 14/07/2025.
//

#include "Renderer/OpenGL/OpenGLHeaders.h"
#include <stdio.h>
#include "../include/RendererAPI/RawMesh.h"
#include "../ErrorHandling/OpenGLErrorHandling.h"
#include "UtilFiles/ReadFile.h"
#include "../Context/OpenGLContext.h"
#include "../../../UtilFiles/Macros.h"
#include <stb_image.h>
#include <string.h>
#include "Renderer/OpenGL/Injector/OpenGLInjector.h"
#include "RendererAPI/Context.h"

unsigned int compileShader (char filePath[], const unsigned int shaderType) {
    const unsigned int shader = glCreateShader(shaderType);
    const int numberOfShaders = 1;
    char *shaderSource = readFile(filePath);

    //Attach shader source to the shader object and compile
    glShaderSource(shader, numberOfShaders, (const GLchar * const*) &shaderSource, NULL);
    free(shaderSource);
    glCompileShader(shader);
    CHECK_OPENGL_ERRORS;
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
    CHECK_OPENGL_ERRORS;
    checkLinkingSuccess(shaderProgram);

    return shaderProgram;
}

/*
 Because we create the shader program in this function,
 this function can be exposed so external developers can add their own shaders
 */
unsigned int openGLRegisterShaderProgram(char *vertexFilePath, char *geometryFullPath, char *fragmentFilePath) {
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

    CHECK_OPENGL_ERRORS;

    return shaderProgram;
}

unsigned int openGLRegisterUBO(const unsigned int blockUniformBindingIndex, const unsigned int bufferSize) {
    unsigned int ubo;
    glGenBuffers(1, &ubo);

    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, bufferSize, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    return ubo;
}


unsigned int openGLGetShaderProgramID(const Context *context, const char *shaderName) {
    OPENGL_CTX;
    for (int i = 0; i < openGLContext->shaderCount; i++) {
        const ShaderProgram *shaderProgram = &openGLContext->shaderPrograms[i];
        if (strcmp(shaderName, shaderProgram->name) == 0) {
            return shaderProgram->id;
        }
    }

    fprintf(stderr, "Failed to find shader program id");
    return 0;
}

ShaderProgram *openGLGetShaderProgram(const Context *context, const unsigned int shaderProgramID) {
    OPENGL_CTX;
    for (int i = 0; i < openGLContext->shaderCount; i++) {
        ShaderProgram *shaderProgram = &openGLContext->shaderPrograms[i];
        if (shaderProgram->id == shaderProgramID) {
            return shaderProgram;
        }
    }

    fprintf(stderr, "Failed to find shader program id");
    return NULL;
}


void openGLSetActiveShaderProgram(const Context *context, const unsigned int programId) {
    OPENGL_CTX;
    glUseProgram(programId);
    openGLContext->activeShaderProgram = programId;

    CHECK_OPENGL_ERRORS;
}
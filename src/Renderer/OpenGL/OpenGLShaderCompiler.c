//
// Created by Carlo Baretta on 14/07/2025.
//

#include <stdlib.h>
#include "OpenGLErrorHandling.h"
#include "glad/Glad.h"
#include "UtilFiles/ReadFile.h"
#include "OpenGLContext.h"



unsigned int compileShader (char fileName[], const unsigned int shaderType) {
    const unsigned int shader = glCreateShader(shaderType);
    char *shaderSource = readFile(fileName);

    //Attach shader source to the shader object and compile
    glShaderSource(shader, 1, (const GLchar * const*) &shaderSource, nullptr);
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
GLuint createShaderProgram(char *vertexFilePath, char *fragmentFilePath) {
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

void setActiveShaderProgram(void *context, GLuint programId) {
    struct OpenGLContext *openGLContext = (struct OpenGLContext *)context;
    glUseProgram(programId);
    openGLContext->activeShaderProgram = programId;
}
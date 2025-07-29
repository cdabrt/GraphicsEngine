//
// Created by Carlo Baretta on 14/07/2025.
//


#include <stdio.h>
#include "OpenGLHeaders.h"

void checkOpenGLError() {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL error %X at %s:%d:", error, __FILE__, __LINE__);
    }
}

void checkCompilationSuccess(const unsigned int shader) {
    const int infoLogLength = 512;
    char infoLog[infoLogLength];
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
        perror(infoLog);
    }
    checkOpenGLError();
}

void checkLinkingSuccess(const unsigned int program) {
    const int infoLogLength = 512;
    char infoLog[infoLogLength];
    int  success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
        snprintf("Program linking failed.\n", sizeof(infoLog), infoLog);
        perror(infoLog);
    }
    checkOpenGLError();
}

void checkUniformLocation(const GLuint uniformLocation) {
    if (uniformLocation == -1) {
        fprintf(stderr, "Uniform does not exist \n");
    }
}
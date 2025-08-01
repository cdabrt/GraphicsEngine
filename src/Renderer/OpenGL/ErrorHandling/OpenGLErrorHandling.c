//
// Created by Carlo Baretta on 14/07/2025.
//

#include <stdio.h>
#include "../OpenGLHeaders.h"
#include "OpenGLErrorHandling.h"

void checkOpenGLErrors(char *file, const int line) {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL error %X at %s:%d\n", error, file, line);
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
    CHECK_OPENGL_ERRORS;
}

void checkLinkingSuccess(const unsigned int program) {
    const int infoLogLength = 512;
    char infoLog[infoLogLength];
    int  success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
        fprintf(stderr,"Program linking failed.\n");
        perror(infoLog);
    }
    CHECK_OPENGL_ERRORS;
}

void checkUniformLocation(const GLuint uniformLocation) {
    if (uniformLocation == -1) {
        fprintf(stderr, "Uniform does not exist \n");
    }
}
//
// Created by Carlo Baretta on 14/07/2025.
//


#include "OpenGLContext.h"
#include <stdlib.h>

void addShaderProgram(struct OpenGLContext *openGLContext, GLuint shaderProgram) {

    const size_t newSize = openGLContext->shaderCount + 1;

    struct ShaderProgram *newArray = realloc(
        openGLContext->shaderPrograms, newSize * sizeof(struct ShaderProgram)
    );

    openGLContext->shaderPrograms = newArray;
    openGLContext->shaderPrograms[openGLContext->shaderCount].id = shaderProgram;
    openGLContext->shaderCount = newSize;
}

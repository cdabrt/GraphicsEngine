//
// Created by Carlo Baretta on 14/07/2025.
//


#include "OpenGLContext.h"
#include <stdlib.h>

void addShaderProgram(struct OpenGLContext *context, const unsigned int shaderProgramID) {
    struct OpenGLContext *openGLContext = (struct OpenGLContext *)context;

    const size_t newSize = openGLContext->shaderCount + 1;

    struct ShaderProgram *shaderPrograms = realloc(
        openGLContext->shaderPrograms, newSize * sizeof(struct ShaderProgram)
    );

    openGLContext->shaderPrograms = shaderPrograms;
    openGLContext->shaderCount = newSize;
    openGLContext->shaderPrograms[openGLContext->shaderCount - 1].id = shaderProgramID;
}

void addVAO(struct OpenGLContext *context, const unsigned int vaoID, const size_t indicesCount) {
    struct OpenGLContext *openGLContext = (struct OpenGLContext *)context;

    const size_t newSize = openGLContext->vaoCount + 1;

    struct VAO *vaos = realloc(
        openGLContext->vaos, newSize * sizeof(struct ShaderProgram)
    );
    openGLContext->vaos = vaos;
    openGLContext->vaoCount = newSize;

    struct VAO vao = {
        vao.id = vaoID,
        vao.indicesCount = indicesCount
    };

    openGLContext->vaos[openGLContext->vaoCount - 1] = vao;
}

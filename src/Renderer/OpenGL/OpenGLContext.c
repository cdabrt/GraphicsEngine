//
// Created by Carlo Baretta on 14/07/2025.
//

#include <stdlib.h>
#include "OpenGLContext.h"
#include "OpenGLMacros.h"

void addShaderProgram(struct OpenGLContext *context, const unsigned int shaderProgramID) {
    OPENGL_CTX;

    const size_t newSize = openGLContext->shaderCount + 1;

    struct ShaderProgram *shaderPrograms = realloc(
        openGLContext->shaderPrograms, newSize * sizeof(struct ShaderProgram)
    );

    openGLContext->shaderPrograms = shaderPrograms;
    openGLContext->shaderCount = newSize;
    openGLContext->shaderPrograms[openGLContext->shaderCount - 1].id = shaderProgramID;
}

void addVAO(struct OpenGLContext *context, const unsigned int vaoID, const size_t indicesCount) {
    OPENGL_CTX;

    const size_t newSize = openGLContext->vaoCount + 1;

    struct VAO *vaos = realloc(
        openGLContext->vaos, newSize * sizeof(struct VAO)
    );
    openGLContext->vaos = vaos;
    openGLContext->vaoCount = newSize;

    struct VAO vao = {
        vao.id = vaoID,
        vao.indicesCount = indicesCount,
        NULL,
        0
    };

    openGLContext->vaos[openGLContext->vaoCount - 1] = vao;
}

void addTexture(struct OpenGLContext *context, struct VAO *vao, const struct Texture texture) {
    OPENGL_CTX;

    const size_t newSize = vao->textureCount + 1;

    struct Texture *textures = realloc(
        vao->textures, newSize * sizeof(struct Texture)
    );
    vao->textures = textures;
    vao->textureCount = newSize;

    vao->textures[vao->textureCount - 1] = texture;
}

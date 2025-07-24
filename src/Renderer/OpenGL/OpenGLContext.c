//
// Created by Carlo Baretta on 14/07/2025.
//

#include <stdlib.h>
#include "OpenGLContext.h"
#include <stdio.h>
#include <string.h>

#include "../../UtilFiles/OpenGLMacrosAndUtils.h"

void addShaderProgram(struct OpenGLContext *context, const unsigned int shaderProgramID, char *shaderName) {
    OPENGL_CTX;

    const size_t newSize = openGLContext->shaderCount + 1;

    struct ShaderProgram *shaderPrograms = realloc(
        openGLContext->shaderPrograms, newSize * sizeof(struct ShaderProgram)
    );

    if (shaderPrograms == NULL) {
        perror("Failed to allocate memory for shader programs");
        exit(EXIT_FAILURE);
    }

    openGLContext->shaderPrograms = shaderPrograms;
    openGLContext->shaderCount = newSize;
    struct ShaderProgram *shaderProgram = &openGLContext->shaderPrograms[openGLContext->shaderCount - 1];
    shaderProgram->id = shaderProgramID;
    shaderProgram->name = shaderName;
}

GLuint getShaderProgramID(struct OpenGLContext *context, const char *shaderName) {
    OPENGL_CTX;
    for (int i = 0; i < openGLContext->shaderCount; i++) {
        const struct ShaderProgram *shaderProgram = &openGLContext->shaderPrograms[i];
        if (strcmp(shaderName, shaderProgram->name) == 0) {
            return shaderProgram->id;
        }
    }

    perror("Failed to find shader program id");
    return 0;
}

void addVAO(struct OpenGLContext *context, const unsigned int vaoID, const size_t indicesCount,
    const unsigned long shaderProgramID) {
    OPENGL_CTX;

    const size_t newSize = openGLContext->vaoCount + 1;

    struct VAO *vaos = realloc(
        openGLContext->vaos, newSize * sizeof(struct VAO)
    );

    if (vaos == NULL) {
        perror("Failed to allocate memory for VAOs");
        exit(EXIT_FAILURE);
    }

    openGLContext->vaos = vaos;
    openGLContext->vaoCount = newSize;

    struct VAO vao = {
        vao.id = vaoID,
        shaderProgramID,
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

    if (textures == NULL) {
        perror("Failed to allocate memory for textures");
        exit(EXIT_FAILURE);
    }

    vao->textures = textures;
    vao->textureCount = newSize;

    vao->textures[vao->textureCount - 1] = texture;
}
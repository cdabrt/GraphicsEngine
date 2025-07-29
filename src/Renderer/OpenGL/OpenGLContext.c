//
// Created by Carlo Baretta on 14/07/2025.
//

#include <stdlib.h>
#include "OpenGLContext.h"
#include <stdio.h>
#include <string.h>

#include "../../UtilFiles/OpenGLMacrosAndUniforms.h"

void registerShaderProgram(struct OpenGLContext *context, const unsigned int shaderProgramID, char *shaderName) {
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

void registerModel(struct OpenGLContext *context, const unsigned int modelID, const size_t indicesCount,
    const unsigned long shaderProgramID) {
    OPENGL_CTX;

    const size_t newSize = openGLContext->modelCount + 1;

    struct Model *models = realloc(
        openGLContext->models, newSize * sizeof(struct Model)
    );

    if (models == NULL) {
        perror("Failed to allocate memory for models");
        exit(EXIT_FAILURE);
    }

    openGLContext->models = models;
    openGLContext->modelCount = newSize;

    struct Model model = {
        model.id = modelID,
        shaderProgramID,
        model.indicesCount = indicesCount,
        NULL,
        0
    };

    openGLContext->models[openGLContext->modelCount - 1] = model;
}

void registerTexture(struct OpenGLContext *context, struct Model *model, const struct Texture texture) {
    OPENGL_CTX;

    const size_t newSize = model->textureCount + 1;

    struct Texture *textures = realloc(
        model->textures, newSize * sizeof(struct Texture)
    );

    if (textures == NULL) {
        perror("Failed to allocate memory for textures");
        exit(EXIT_FAILURE);
    }

    model->textures = textures;
    model->textureCount = newSize;

    model->textures[model->textureCount - 1] = texture;
}
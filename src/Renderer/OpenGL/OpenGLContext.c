//
// Created by Carlo Baretta on 14/07/2025.
//

#include <stdlib.h>
#include "OpenGLContext.h"
#include <string.h>
#include "UtilFiles/GeneralErrorHandling.h"

void registerShaderProgram(struct OpenGLContext *openGLContext, const unsigned int shaderProgramID, char *shaderName) {
    const size_t newSize = openGLContext->shaderCount + 1;

    struct ShaderProgram *shaderPrograms = realloc(
        openGLContext->shaderPrograms, newSize * sizeof(struct ShaderProgram)
    );
    checkMalloc(shaderPrograms);

    openGLContext->shaderPrograms = shaderPrograms;
    openGLContext->shaderCount = newSize;
    struct ShaderProgram *shaderProgram = &openGLContext->shaderPrograms[openGLContext->shaderCount - 1];
    shaderProgram->id = shaderProgramID;
    shaderProgram->name = shaderName;
}

void registerModel(struct OpenGLContext *openGLContext, const unsigned int modelID, const size_t indicesCount,
    char* modelName, const unsigned long shaderProgramID) {

    const size_t newSize = openGLContext->modelCount + 1;

    struct Model *models = realloc(
        openGLContext->models, newSize * sizeof(struct Model)
    );
    checkMalloc(models);

    openGLContext->models = models;
    openGLContext->modelCount = newSize;

    mat4s *localTransformations = malloc(sizeof(mat4s));
    checkMalloc(localTransformations);
    mat4s *worldTransformations = malloc(sizeof(mat4s));
    checkMalloc(worldTransformations);

    *localTransformations = glms_mat4_identity();
    *worldTransformations = glms_mat4_identity();

    struct Model model = {
        modelName,
        model.id = modelID,
        shaderProgramID,
        model.indicesCount = indicesCount,
        NULL,
        0,
        localTransformations,
        worldTransformations
    };

    openGLContext->models[openGLContext->modelCount - 1] = model;
}

void registerTexture(struct Model *model, const struct Texture texture) {
    const size_t newSize = model->textureCount + 1;

    struct Texture *textures = realloc(
        model->textures, newSize * sizeof(struct Texture)
    );
    checkMalloc(textures);

    model->textures = textures;
    model->textureCount = newSize;

    model->textures[model->textureCount - 1] = texture;
}
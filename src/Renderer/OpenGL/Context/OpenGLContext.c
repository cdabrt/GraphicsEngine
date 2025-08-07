//
// Created by Carlo Baretta on 14/07/2025.
//

#include <stdlib.h>
#include "OpenGLContext.h"
#include <string.h>
#include "UtilFiles/GeneralErrorHandling.h"
#include "RendererAPI/Transformation.h"
#include "RendererAPI/Texture.h"

void registerShaderProgram(OpenGLContext *openGLContext, const unsigned int shaderProgramID, char *shaderName) {
    const size_t newSize = openGLContext->shaderCount + 1;

    ShaderProgram *shaderPrograms = realloc(
        openGLContext->shaderPrograms, newSize * sizeof(ShaderProgram)
    );
    checkMalloc(shaderPrograms);

    openGLContext->shaderPrograms = shaderPrograms;
    openGLContext->shaderCount = newSize;
    ShaderProgram *shaderProgram = &openGLContext->shaderPrograms[openGLContext->shaderCount - 1];
    shaderProgram->id = shaderProgramID;
    shaderProgram->name = shaderName;
}

void registerModel(OpenGLContext *openGLContext, const unsigned int modelID, const size_t indicesCount,
    char* modelName, const unsigned long shaderProgramID) {

    const size_t newSize = openGLContext->modelCount + 1;

    Model *models = realloc(
        openGLContext->models, newSize * sizeof(Model)
    );
    checkMalloc(models);

    openGLContext->models = models;
    openGLContext->modelCount = newSize;

    mat4s localTransformations = glms_mat4_identity();
    mat4s worldTransformations = glms_mat4_identity();

    Transformation transformations = {localTransformations, worldTransformations};

    Model model = {
        modelName,
        model.id = modelID,
        shaderProgramID,
        model.indicesCount = indicesCount,
        NULL,
        0,
        transformations,
    };

    openGLContext->models[openGLContext->modelCount - 1] = model;
}

void registerTexture(Model *model, const Texture texture) {
    const size_t newSize = model->textureCount + 1;

    Texture *textures = realloc(
        model->textures, newSize * sizeof(Texture)
    );
    checkMalloc(textures);

    model->textures = textures;
    model->textureCount = newSize;

    model->textures[model->textureCount - 1] = texture;
}
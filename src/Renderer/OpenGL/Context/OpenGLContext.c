//
// Created by Carlo Baretta on 14/07/2025.
//

#include <stdlib.h>
#include "OpenGLContext.h"
#include <string.h>
#include "Renderer/OpenGL/Injector/OpenGLInjector.h"
#include "UtilFiles/GeneralErrorHandling.h"
#include "RendererAPI/Transformation.h"
#include "RendererAPI/Texture.h"

void registerUBO(ShaderProgram *shaderProgram, char *uboName, const unsigned long uboID,
    const unsigned long uniformBlockBindingIndex, const unsigned long bufferSize, void* structData) {
    const size_t newSize = shaderProgram->uboCount + 1;

    UBO *ubos = realloc(
        shaderProgram->ubos, newSize * sizeof(UBO)
    );
    checkMalloc(ubos);

    shaderProgram->ubos = ubos;
    shaderProgram->uboCount = newSize;
    UBO *ubo = &shaderProgram->ubos[shaderProgram->uboCount - 1];
    ubo->id = uboID;
    ubo->name = uboName;
    ubo->uniformBlockBindingIndex = uniformBlockBindingIndex;
    ubo->bufferSize = bufferSize;
    ubo->data = structData;
}

void registerShaderProgram(OpenGLContext *context, const unsigned int shaderProgramID, char *shaderName) {

    const size_t newSize = context->shaderCount + 1;

    ShaderProgram *shaderPrograms = realloc(
        context->shaderPrograms, newSize * sizeof(ShaderProgram)
    );
    checkMalloc(shaderPrograms);

    context->shaderPrograms = shaderPrograms;
    context->shaderCount = newSize;
    ShaderProgram *shaderProgram = &context->shaderPrograms[context->shaderCount - 1];
    shaderProgram->id = shaderProgramID;
    shaderProgram->name = shaderName;
    shaderProgram->ubos = memset(shaderProgram->ubos, 0, 0);
    shaderProgram->uboCount = 0;
}

void registerModel(OpenGLContext *context, const unsigned int modelID, const size_t indicesCount,
    char* modelName, const unsigned long shaderProgramID) {

    const size_t newSize = context->modelCount + 1;

    Model *models = realloc(
        context->models, newSize * sizeof(Model)
    );
    checkMalloc(models);

    context->models = models;
    context->modelCount = newSize;

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

    context->models[context->modelCount - 1] = model;
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
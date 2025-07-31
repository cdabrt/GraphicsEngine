//
// Created by Carlo Baretta on 20/07/2025.
//

#include <stdio.h>
#include "../include/RendererAPI/RawMesh.h"
#include "Renderer/OpenGL/OpenGLContext.h"
#include "../../../UtilFiles/MacrosAndUniforms.h"
#include <stb_image.h>
#include <string.h>
#include "Renderer/OpenGL/OpenGLErrorHandling.h"
#include "Renderer/OpenGL/OpenGLHeaders.h"
#include "Renderer/OpenGL/Injector/OpenGLInjector.h"
#include "RendererAPI/Context.h"

void registerVBO(const struct RawMesh *mesh) {
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertexDataSize, mesh->vertices, GL_STATIC_DRAW);

    CHECK_OPENGL_ERRORS;
}

void registerEBO(const struct RawMesh *mesh) {
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indicesDataSize, mesh->indices, GL_STATIC_DRAW);

    CHECK_OPENGL_ERRORS;
}

void layOutVertexAttributes() {
    const int vertexAttribIndex = 0;
    const int vertexColourAttribIndex = 1;
    const int textureCoordinatesIndex = 2;
    const int vertexBlockSize = 3;
    const int textureCoordinatesBlockSize = 2;
    const int stride = 8;

    //Vertex position
    glVertexAttribPointer(vertexAttribIndex, vertexBlockSize, GL_FLOAT, GL_FALSE,
        stride * sizeof(float), NULL);
    glEnableVertexAttribArray(vertexAttribIndex);

    //Colour position
    glVertexAttribPointer(vertexColourAttribIndex, vertexBlockSize, GL_FLOAT, GL_FALSE,
        stride * sizeof(float), (void*)(vertexBlockSize * sizeof(float)));
    glEnableVertexAttribArray(vertexColourAttribIndex);

    //Texture coordinates position
    glVertexAttribPointer(textureCoordinatesIndex, textureCoordinatesBlockSize, GL_FLOAT, GL_FALSE,
        stride * sizeof(float), (void*)(vertexBlockSize * textureCoordinatesBlockSize * sizeof(float)));
    glEnableVertexAttribArray(textureCoordinatesIndex);

    CHECK_OPENGL_ERRORS;
}



//TODO: Register static mesh, put it into one big VBO and use glMultiDrawIndirect for frustum culling of the big static VBO.
//  The dynamic meshes still need to be frustum culled
//  Also look into instancing (trees, bullets, etc)
unsigned int openGLRegisterMesh(const struct Context *context, const struct RawMesh *mesh, char *modelName, const unsigned long shaderProgramID) {
    OPENGL_CTX;

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    CHECK_OPENGL_ERRORS;

    registerVBO(mesh);
    registerEBO(mesh);
    layOutVertexAttributes();

    registerModel(openGLContext, VAO, mesh->indicesDataSize, modelName, shaderProgramID);
    openGLRegisterTextures(mesh->textures, mesh->textureCount, &openGLContext->models[openGLContext->modelCount - 1]);

    return VAO;
}

struct Model *openGLGetModel(const struct Context *context, const unsigned int modelID) {
    OPENGL_CTX;
    for (int i = 0; i < openGLContext->modelCount; i++) {
        struct Model *model = &openGLContext->models[i];
        if (model->id == modelID) {
            return model;
        }
    }

    fprintf(stderr, "Failed to find model");
    return NULL;
}

unsigned int openGLGetModelID(const struct Context *context, const char *modelName) {
    OPENGL_CTX;
    for (int i = 0; i < openGLContext->modelCount; i++) {
        const struct Model *model = &openGLContext->models[i];
        if (strcmp(modelName, model->name) == 0) {
            return model->id;
        }
    }

    fprintf(stderr, "Failed to find model id");
    return 0;
}
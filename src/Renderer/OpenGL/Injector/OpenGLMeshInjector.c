//
// Created by Carlo Baretta on 20/07/2025.
//

#include <stdio.h>
#include "../include/RendererAPI/Mesh.h"
#include "Renderer/OpenGL/OpenGLContext.h"
#include "../../../UtilFiles/OpenGLMacrosAndUniforms.h"
#include <stb_image.h>
#include <string.h>
#include "Renderer/OpenGL/OpenGLHeaders.h"
#include "Renderer/OpenGL/Injector/OpenGLInjector.h"



void registerVBO(const struct Mesh *mesh) {
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertexDataSize, mesh->vertices, GL_STATIC_DRAW);
}

void registerEBO(const struct Mesh *mesh) {
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indicesDataSize, mesh->indices, GL_STATIC_DRAW); ;
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
}



//TODO: Register static mesh, put it into one big VBO and use glMultiDrawIndirect for frustum culling of the big static VBO.
//  The dynamic meshes still need to be frustum culled
//  Also look into instancing (trees, bullets, etc)
unsigned int openGLRegisterMesh(void *context, const struct Mesh *mesh, const unsigned long shaderProgramID) {
    OPENGL_CTX;

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    registerVBO(mesh);
    registerEBO(mesh);
    layOutVertexAttributes();

    addVAO(openGLContext, VAO, mesh->indicesDataSize, shaderProgramID);
    openGLRegisterTextures(openGLContext, mesh->textures, mesh->textureCount, &openGLContext->vaos[openGLContext->vaoCount - 1]);

    return VAO;
}
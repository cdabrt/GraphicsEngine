//
// Created by Carlo Baretta on 20/07/2025.
//

#ifndef MESH_H
#define MESH_H

#include "Renderer/OpenGL/OpenGLHeaders.h"
#include "UtilFiles/OpenGLMacrosAndUniforms.h"

struct Texture {
    char *path;
    enum TextureType type;
    char *uniformName;
    unsigned int id;
    int textureUnit;
};

struct Mesh {
    const float *vertices;
    const int *indices;
    const long vertexDataSize;
    const long indicesDataSize;
    struct Texture *textures;
    size_t textureCount;
};

#endif //MESH_H

//
// Created by Carlo Baretta on 20/07/2025.
//

#ifndef MESH_H
#define MESH_H

#include <Renderer/OpenGL/OpenGLHeaders.h>

enum TextureType {
    DIFFUSE,
    NORMAL,
    SPECULAR,
    AO,
};

struct Texture {
    char *path;
    enum TextureType type;
    char *uniformName;
    GLuint id;
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

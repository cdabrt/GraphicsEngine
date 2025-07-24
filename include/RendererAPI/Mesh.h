//
// Created by Carlo Baretta on 20/07/2025.
//

#ifndef MESH_H
#define MESH_H

#include "Renderer/OpenGL/OpenGLHeaders.h"

enum TextureType {
    DIFFUSE,
    NORMAL_MAP,
    SPECULAR_MAP,
    AO_MAP,
    HEIGHT_MAP,
    EMISSIVE_MAP,
    CUBE_MAP,
    LUT
};

inline char *getBaseTextureTypeString(const enum TextureType textureType)
{
    char *string = "\0";

    switch(textureType) {
        case DIFFUSE: string="diffuse"; break;
        case NORMAL_MAP: string="normalMap"; break;
        case SPECULAR_MAP: string="specularMap"; break;
        case AO_MAP: string="aoMap"; break;
        case HEIGHT_MAP: string="heightMap"; break;
        case EMISSIVE_MAP: string="emissiveMap"; break;
        case CUBE_MAP: string="cubeMap"; break;
        case LUT: string="lut"; break;
        default:
            perror("Unknown texture type");
    }

    return string;
}

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

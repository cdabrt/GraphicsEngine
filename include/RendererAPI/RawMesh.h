//
// Created by Carlo Baretta on 20/07/2025.
//

#ifndef MESH_H
#define MESH_H

#include "UtilFiles/Macros.h"
#include "RendererAPI/Texture.h"

/**
 * RawMesh
 * A DTO containing vertex and texture data. This data is used for the registration of the mesh data (@ref openGLRegisterMesh) in a @ref Mesh
 *
 * @param vertices the vertices of the mesh.
 * @param indices the indices of the mesh.
 * @param vertexDataSize the amount of vertices.
 * @param indicesDataSize the amount of indices.
 * @param textures the textures of the mesh.
 * @param textureCount the amount of textures.
 */
typedef struct RawMesh {
    const float *vertices;
    const int *indices;
    const long vertexDataSize;
    const long indicesDataSize;
    Texture *textures;
    size_t textureCount;
} RawMesh;

#endif //MESH_H

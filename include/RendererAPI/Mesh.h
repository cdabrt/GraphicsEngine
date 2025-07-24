//
// Created by Carlo Baretta on 20/07/2025.
//

#ifndef MESH_H
#define MESH_H

#include "Renderer/OpenGL/OpenGLHeaders.h"
#include "UtilFiles/OpenGLMacrosAndUniforms.h"

/**
 * Texture
 * A DTO containing texture data. This data is used for the registration of the texture data (@ref openGLRegisterMesh, @ref openGLRegisterTextures) in a @ref VAO
 *
 * @param path the path to the texture.
 * @param TextureType the type of texture.
 * @param uniformName the uniformName that the texture is associated to in the vertex or fragment shader in the active shader program registered in the @ref VAO.
 * @param id the id of the texture. The id does not have to be set manually. This is done under the hood in the @ref RendererInjector.
 * Give it any value when manually creating the struct.
 * @param textureUnit the associated texture unit of the texture: The binding in the GPU that allows a shader to access the texture.
 * A textureUnit of 0 means that this texture lives in slot 0. The textureUnit also does not have to be set manually.
 * The initialization of textureUnit is also done under the hood in the @ref RendererInjector.
 * Give it any value when manually creating the struct.
 */
struct Texture {
    char *path;
    enum TextureType type;
    char *uniformName;
    unsigned int id;
    int textureUnit;
};

/**
 * Mesh
 * A DTO containing vertex and texture data. This data is used for the registration of the mesh data (@ref openGLRegisterMesh) in a @ref VAO
 *
 * @param vertices the vertices of the mesh.
 * @param indices the indices of the mesh.
 * @param vertexDataSize the amount of vertices.
 * @param indicesDataSize the amount of indices.
 * @param textures the textures of the mesh.
 * @param textureCount the amount of textures.
 */
struct Mesh {
    const float *vertices;
    const int *indices;
    const long vertexDataSize;
    const long indicesDataSize;
    struct Texture *textures;
    size_t textureCount;
};

#endif //MESH_H

//
// Created by Carlo Baretta on 07/08/2025.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include "Renderer/OpenGL/OpenGLHeaders.h"

typedef enum TextureType {
    DIFFUSE,
    NORMAL_MAP,
    SPECULAR_MAP,
    AO_MAP,
    HEIGHT_MAP,
    EMISSIVE_MAP,
    CUBE_MAP,
    LUT
} TextureType;

inline char *getBaseTextureTypeUniformString(const TextureType textureType)
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

/**
 * Texture
 * A DTO containing texture data. This data is used for the registration of the texture data (@ref openGLRegisterMesh, @ref openGLRegisterTextures) in a @ref Model
 *
 * @param path the path to the texture.
 * @param TextureType the type of texture.
 * @param uniformName the uniformName that the texture is associated to in the vertex or fragment shader in the active shader program registered in the @ref Model.
 * @param id the id of the texture. The id does not have to be set manually. This is done under the hood in the @ref RendererInjector.
 * Give it any value when manually creating the struct.
 * @param textureUnit the associated texture unit of the texture: The binding in the GPU that allows a shader to access the texture.
 * A textureUnit of 0 means that this texture lives in slot 0. The textureUnit also does not have to be set manually.
 * The initialization of textureUnit is also done under the hood in the @ref RendererInjector.
 * Give it any value when manually creating the struct.
 */
typedef struct Texture {
    char *path;
    TextureType type;
    char *uniformName;
    unsigned int id;
    int textureUnit;
} Texture;

#endif //TEXTURE_H

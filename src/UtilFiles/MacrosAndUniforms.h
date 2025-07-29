//
// Created by carlo on 17-7-2025.
//

#ifndef OPENGLMACROS_H
#define OPENGLMACROS_H
#include <stdio.h>
#include <Renderer/OpenGL/OpenGLContext.h>

/**
 * OPENGL_CTX
 * Declares and initializes a pointer to the OpenGL rendering context implementation.
 *
 * @param context the renderer context.
 *
 * @note This macro implicitly creates a variable called `openGLContext`. Use carefully to avoid naming conflicts.
 *
 * \b Expands to:
 * @code
 *      struct OpenGLContext *openGLContext = (struct OpenGLContext *)context;
 * @endcode
 *
 * \b Usage:
 * @code
 *      void someOpenGLFunction(void *context) {
 *          OPENGL_CTX; // Now you can use `openGLContext`
 *           ...
 *      }
 * @endcode
 */
#define OPENGL_CTX struct OpenGLContext *openGLContext = (struct OpenGLContext *)context



typedef enum {
    BASE_SHADER,
    WIREFRAME_SHADER,
} BaseShader;

inline char *getBaseShaderUniformString(const BaseShader shader)
{
    char *string = "\0";

    switch(shader) {
        case BASE_SHADER: string="baseShader"; break;
        case WIREFRAME_SHADER: string="wireframeShader"; break;
        default:
            perror("Unknown shader type");
    }

    return string;
}




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

inline char *getBaseTextureTypeUniformString(const enum TextureType textureType)
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



enum MeshUniforms {
    TRANSFORM
};

inline char *getBaseMeshUniformString(const enum TextureType textureType)
{
    char *string = "\0";

    switch(textureType) {
        case TRANSFORM: string="transform"; break;
        default:
            perror("Unknown mesh uniform");
    }

    return string;
}

#endif //OPENGLMACROS_H

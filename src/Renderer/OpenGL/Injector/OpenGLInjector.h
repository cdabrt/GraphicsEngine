//
// Created by Carlo Baretta on 14/07/2025.
//

#ifndef OPENGLSHADERINJECTOR_H
#define OPENGLSHADERINJECTOR_H
#include <../include/RendererAPI/Mesh.h>

/**
 * openGLCreateShaderProgram
 * Creates an OpenGL shader program
 *
 * @param vertexFilePath path to vertex shader file.
 * @param geometryFullPath path to geometry shader file. <b>This file is optional</b>.
 * @param fragmentFilePath path to fragment shader file.
 */
unsigned int openGLCreateShaderProgram(char *vertexFilePath, char *geometryFullPath, char *fragmentFilePath);

/**
 * openGLSetActiveShaderProgram
 * Sets an OpenGL Shader Program as active.
 *
 * @param context the renderer context.
 * @param programId ID of the shader program.
 */
void openGLSetActiveShaderProgram(void *context, unsigned long programId);

/**
 * openGLRegisterMesh
 * Registers a mesh to be rendered.
 *
 * @param context the renderer context.
 * @param mesh the mesh to be registered.
 * @param vertices the vertex matrix of the mesh.
 * @param indices the index matrix of the mesh.
 * @param vertexDataSize how many items there are in the vertex matrix.
 * @param indicesDataSize how many items there are in the index matrix.
 */
void openGLRegisterMesh(void *context, const struct Mesh *mesh);

/**
 * registerTextures
 * Registers a list of textures and adds those textures to the VAO.
 *
 * @param context the renderer context.
 * @param textures the to be added texture.
 * @param textureCount the number of textures that need to be added.
 * @param vao the vao of which the textures need to be added to.
 */
void registerTextures(struct OpenGLContext *context, const struct Texture *textures, size_t textureCount, struct VAO *vao);
#endif //OPENGLSHADERINJECTOR_H

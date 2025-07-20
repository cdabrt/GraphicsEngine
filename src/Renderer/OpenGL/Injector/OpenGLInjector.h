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
 * @param fragmentFilePath path to fragment shader file.
 */
unsigned int openGLCreateShaderProgram(char *vertexFilePath, char *fragmentFilePath);

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
void openGLRegisterMesh(void *context, struct Mesh mesh);
#endif //OPENGLSHADERINJECTOR_H

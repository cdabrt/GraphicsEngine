//
// Created by Carlo Baretta on 14/07/2025.
//

#ifndef OPENGLSHADERINJECTOR_H
#define OPENGLSHADERINJECTOR_H
#include <../include/RendererAPI/RawMesh.h>

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
 * openGLGetShaderProgramID
 * Gets the shader program with the provided shader name.
 *
 * @param context @ref OpenGLContext.
 * @param shaderName name of the shader program.
 */
unsigned int openGLGetShaderProgramID(void *context, const char *shaderName);

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
* @param shaderProgramID ID of the shader program that is associated with the mesh. If no ID is provided the renderer
 * will use the active shader program instead.
 */
unsigned int openGLRegisterMesh(void *context, const struct RawMesh *mesh, unsigned long shaderProgramID);

/**
 * registerTextures
 * Registers a list of textures and adds those textures to the Modelf Model.
 *
 * @param context the renderer context.
 * @param textures the to be added texture.
 * @param textureCount the number of textures that need to be added.
 * @param model the model of which the textures need to be added to.
 */
void openGLRegisterTextures(struct OpenGLContext *context, const struct Texture *textures, size_t textureCount, struct Model *model);
#endif //OPENGLSHADERINJECTOR_H
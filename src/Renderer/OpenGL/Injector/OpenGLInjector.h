//
// Created by Carlo Baretta on 14/07/2025.
//

#ifndef OPENGLSHADERINJECTOR_H
#define OPENGLSHADERINJECTOR_H
#include <../include/RendererAPI/RawMesh.h>
#include "RendererAPI/Context.h"

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
unsigned int openGLGetShaderProgramID(const Context *context, const char *shaderName);

/**
 * openGLSetActiveShaderProgram
 * Sets an OpenGL Shader Program as active.
 *
 * @param context the renderer context.
 * @param programId ID of the shader program.
 */
void openGLSetActiveShaderProgram(const Context *context, unsigned long programId);

/**
 * openGLRegisterMesh
 * Registers a mesh to be rendered.
 *
 * @param context the renderer context.
 * @param mesh the mesh to be registered.
 * @param modelName the name of the resulting model that will be created using the mesh.
 * @param shaderProgramID ID of the shader program that is associated with the mesh. If no ID is provided the renderer
 * will use the active shader program instead.
 */
unsigned int openGLRegisterMesh(const Context *context, const RawMesh *mesh, char *modelName, unsigned long shaderProgramID);

/**
 * openGLGetModel
 * Gets the model with the provided model ID.
 *
 * @param context @ref OpenGLContext.
 * @param modelID ID of the model.
 */
Model *openGLGetModel(const Context *context, unsigned int modelID);

/**
 * openGLGetModel
 * Gets the model with the provided model name.
 *
 * @param context @ref OpenGLContext.
 * @param modelName name of the model.
 */
unsigned int openGLGetModelID(const Context *context, const char *modelName);

/**
 * registerTextures
 * Registers a list of textures and adds those textures to the Modelf Model.
 *
 * @param textures the to be added texture.
 * @param textureCount the number of textures that need to be added.
 * @param model the model of which the textures need to be added to.
 */
void openGLRegisterTextures(const Texture *textures, size_t textureCount, Model *model);
#endif //OPENGLSHADERINJECTOR_H
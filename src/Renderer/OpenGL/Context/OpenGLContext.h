//
// Created by Carlo Baretta on 14/07/2025.
//

#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H
#include <RendererAPI/RawMesh.h>
#include "Renderer/OpenGL/OpenGLHeaders.h"
#include "../include/RendererAPI/Model.h"

/**
 * UBO
 * Struct representing an OpenGL UBO.
 *
 * @param id the id of the UBO.
 * @param name the name of the UBO.
 * @param uniformBlockBindingIndex the index of the UBO block binding.
 * @param bufferSize the buffer size of the UBO.
 * @param data the struct containing the necessary UBO data.
 * @note \b IMPORTANT: Make absolutely sure that the struct you created that contains and represents your UBO Data
 * is ordered in the exact same way and consists of the same datastructures. Your shader will otherwise not work.
 */
typedef struct UBO {
    GLuint id;
    char *name;
    unsigned int uniformBlockBindingIndex;
    unsigned int bufferSize;
    void *data;
} UBO;

/**
 * ShaderProgram
 * Struct representing an OpenGL shader program.
 *
 * @param id the id of the shader program.
 */
typedef struct ShaderProgram {
    GLuint id;
    char *name;
    UBO *ubos;
    unsigned int uboCount;
} ShaderProgram;

/*
  Function pointers have not been used for creating these patterns. They have been used in the renderer factory,
  however one could argue that for the functions of OpenGLContext this is overkill.
  registerShaderProgram, registerModel, and registerTexture are specifically only used within the
  OpenGLRenderer implementation. The complexity these function pointers add are unnecessary in this case.
  */

/**
 * OpenGLContext
 * The OpenGL implementation of the renderer context.
 *
 * @param window the active @ref GLFWwindow.
 * @param shaderPrograms the list of OpenGL shader programs.
 * @param models the list of models.
 * @param shaderCount the number of shader programs.
 * @param modelCount the number of models.
 * @param activeShaderProgram the active shader program, this is the shader that is currently used by the renderer.
 */
typedef struct OpenGLContext {
    ShaderProgram *shaderPrograms;
    Model *models;
    size_t shaderCount;
    size_t modelCount;
    GLuint activeShaderProgram;
} OpenGLContext;

/**
 * registerShaderProgram
 * Registers a shader program to the list of shader programs of @ref OpenGLContext.
 *
 * @param context @ref OpenGLContext.
 * @param shaderProgramID the ID of the shader program.
 * @param shaderName the name of the shader program.
 */
void registerShaderProgram(OpenGLContext *context, unsigned int shaderProgramID, char *shaderName);

/**
 * registerUBO
 * Registers a UBO to the list of UBOs of @ref ShaderProgram.
 *
 * @param shaderProgram the shader program.
 * @param uboName the name of the UBO.
 * @param uboID the id of the UBO.
 * @param uniformBlockBindingIndex the binding point of the UBO.
 * @param bufferSize the buffer size of the UBO.
 * @param structData a pointer to the structData that has to be added. The structData contains the necessary UBO data.
 * @note \b IMPORTANT: Make absolutely sure that the struct you created that contains and represents your UBO Data
 * is ordered in the exact same way and consists of the same datastructures. Your shader will otherwise not work.
 */
void registerUBO(ShaderProgram *shaderProgram, char *uboName, unsigned long uboID,
    unsigned long uniformBlockBindingIndex, unsigned long bufferSize, void * structData);

/**
 * registerModel
 * Registers a Model to the list of models of @ref OpenGLContext.
 *
 * @param context @ref OpenGLContext.
 * @param modelID the ID of the model.
 * @param indicesCount the number of indices of all the meshes that belong to the model.
 * @param modelName the name of the model.
 * @param shaderProgramID ID of the shader program that is associated with the model.
 */
void registerModel(OpenGLContext *context, unsigned int modelID, size_t indicesCount,
    char* modelName, unsigned long shaderProgramID);

/**
 * registerTexture
 * Registers a texture to the ModelMesh.
 *
 * @param model the Mesh the texture needs to be added to.
 * @param texture the texture that needs to be added to the model.
 */
void registerTexture(Model *model, Texture texture);

#endif //OPENGLCONTEXT_H

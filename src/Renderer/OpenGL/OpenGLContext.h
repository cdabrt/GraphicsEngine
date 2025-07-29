//
// Created by Carlo Baretta on 14/07/2025.
//

#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H
#include <RendererAPI/RawMesh.h>
#include "Renderer/OpenGL/OpenGLHeaders.h"

/**
 * ShaderProgram
 * Struct representing an OpenGL shader program.
 *
 * @param id the id of the shader program.
 */
struct ShaderProgram {
    GLuint id;
    char *name;
};

/**
 * Model
 * Struct representing an OpenGL Model.
 *
 * @param id the id of the model.
 * @param indicesCount the amount of indices of all the meshes that belong to the model.
 * @param shaderProgramID it is possible for no shaderProgramID to be defined.
 * @param textures the list of textures.
 * @param textureCount the amount of textures in the list of textures.
 */
struct Model {
    GLuint id;
    GLuint shaderProgramID;
    size_t indicesCount;
    struct Texture *textures;
    size_t textureCount;
};

/*
  In the future use function pointers in the struct, so that the variables within the struct can be used in the function.
  Then create an init function, like is done in the factories, that pass the pointers to the functions.
  Perhaps could've just used C++ and write the entire program in C except for when creating these patterns.
  However, one could argue this is too much, as registerregisterShaderProgram and registerregisterModel are specifically only used within the
  OpenGLRenderer implementation. This avoids unnecessary complexity when adding these function pointers.
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
struct OpenGLContext {
    GLFWwindow *window;
    struct ShaderProgram *shaderPrograms;
    struct Model *models;
    size_t shaderCount;
    size_t modelCount;
    GLuint activeShaderProgram;
};

/**
 * registerShaderProgram
 * Registers a shader program to the list of shader programs of @ref OpenGLContext.
 *
 * @param context @ref OpenGLContext.
 * @param shaderProgramID the ID of the shader program.
 * @param shaderName name of the shader program.
 */
void registerShaderProgram(struct OpenGLContext *context, unsigned int shaderProgramID, char *shaderName);

/**
 * registerModel
 * Registers a Model to the list of models of @ref OpenGLContext.
 *
 * @param context @ref OpenGLContext.
 * @param modelID the ID of the model.
 * @param indicesCount the number of indices of all the meshes that belong to the model.
 * @param shaderProgramID ID of the shader program that is associated with the model.
 */
void registerModel(struct OpenGLContext *context, unsigned int modelID, size_t indicesCount, unsigned long shaderProgramID);

/**
 * registerTexture
 * Registers a texture to the ModelMesh.
 *
 * @param context @ref OpenGLContext.
 * @param model the Mesh the texture needs to be added to.
 * @param texture the texture that needs to be added to the model.
 */
void registerTexture(struct OpenGLContext *context, struct Model *model, struct Texture texture);

#endif //OPENGLCONTEXT_H

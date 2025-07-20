//
// Created by Carlo Baretta on 14/07/2025.
//

#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H
#include <RendererAPI/Mesh.h>
#include "Renderer/OpenGL/OpenGLHeaders.h"

/**
 * ShaderProgram
 * Struct representing an OpenGL shader program.
 *
 * @param id the id of the shader program.
 */
struct ShaderProgram {
    GLuint id;
};

/**
 * VAO
 * Struct representing an OpenGL VAO.
 *
 * @param id the id of the VAO.
 * @param indicesCount the amount of indices of all the meshes that belong to the VAO.
 */
struct VAO {
    GLuint id;
    size_t indicesCount;
    struct Texture *textures;
    size_t textureCount;
};

/*
  In the future use function pointers in the struct, so that the variables within the struct can be used in the function.
  Then create an init function, like is done in the factories, that pass the pointers to the functions.
  Perhaps could've just used C++ and write the entire program in C except for when creating these patterns.
  However, one could argue this is too much, as addShaderProgram and addVAO are specifically only used within the
  OpenGLRenderer implementation. This avoids unnecessary complexity when adding these function pointers.
  */

/**
 * OpenGLContext
 * The OpenGL implementation of the renderer context.
 *
 * @param window the active @ref GLFWwindow.
 * @param shaderPrograms the list of OpenGL shader programs.
 * @param vaos the list of OpenGL VAOs.
 * @param shaderCount the number of shader programs.
 * @param vaoCount the number of VAOs.
 * @param activeShaderProgram the active shader program, this is the shader that is currently used by the renderer.
 */
struct OpenGLContext {
    GLFWwindow *window;
    struct ShaderProgram *shaderPrograms;
    struct VAO *vaos;
    size_t shaderCount;
    size_t vaoCount;
    GLuint activeShaderProgram;
};

/**
 * addShaderProgram
 * Adds a shader program to the list of shader programs of @ref OpenGLContext.
 *
 * @param context @ref OpenGLContext.
 * @param shaderProgramID the ID of the shader program.
 */
void addShaderProgram(struct OpenGLContext *context, unsigned int shaderProgramID);

/**
 * addShaderProgram
 * Adds a VAO to the list of VAOs of @ref OpenGLContext.
 *
 * @param context @ref OpenGLContext.
 * @param vao the ID of the VAO.
 * @param indicesCount the number of indices of all the meshes that belong to the VAO.
 */
void addVAO(struct OpenGLContext *context, unsigned int vao, size_t indicesCount);

/**
 * addTexture
 * Adds a texture to the VAO.
 *
 * @param context @ref OpenGLContext.
 * @param vao the VAO the texture needs to be added to.
 * @param texture the texture that needs to be added to the VAO.
 */
void addTexture(struct OpenGLContext *context, struct VAO *vao, struct Texture texture);

#endif //OPENGLCONTEXT_H

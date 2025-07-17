//
// Created by Carlo Baretta on 14/07/2025.
//

#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H
#include "GLFW/glfw3.h"

struct OpenGLContext;

struct ShaderProgram {
    GLuint id;
};

struct VAO {
    GLuint id;
    size_t indicesCount;
};

//In the future use function pointers in the struct, so that the variables within the struct can be used in the function.
//Then create an init function, like is done in the factories, that pass the pointers to the functions.
//Perhaps could've just used C++ and write the entire program in C except for when creating these patterns.

struct OpenGLContext {
    GLFWwindow *window;

    struct ShaderProgram *shaderPrograms;
    struct VAO *vaos;
    size_t shaderCount;
    size_t vaoCount;
    GLuint activeShaderProgram;
};

void addShaderProgram(struct OpenGLContext *context, unsigned int shaderProgramID);
void addVAO(struct OpenGLContext *context, unsigned int vao, size_t indicesCount);

#endif //OPENGLCONTEXT_H

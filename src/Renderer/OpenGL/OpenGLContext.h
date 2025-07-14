//
// Created by Carlo Baretta on 14/07/2025.
//

#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H
#include "GLFW/glfw3.h"

struct ShaderProgram {
    GLuint id;
};

struct OpenGLContext {
    GLFWwindow *window;

    struct ShaderProgram *shaderPrograms;
    size_t shaderCount;
    GLuint activeShaderProgram;
};

void addShaderProgram(struct OpenGLContext *openGLContext, GLuint shaderProgram);

#endif //OPENGLCONTEXT_H

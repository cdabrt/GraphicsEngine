//
// Created by Carlo Baretta on 01/08/2025.
//

#ifndef CONTEXT_H
#define CONTEXT_H
#include "Renderer/OpenGL/OpenGLHeaders.h"

/**
 * Context
 * The OpenGL implementation of the renderer context.
 *
 * @param window the active @ref GLFWwindow.
 * @param backendSpecificContext the backend specific implementation of the renderer context.
 */
struct Context {
    GLFWwindow *window;
    void *backendSpecificContext;
};

#endif //CONTEXT_H

//
// Created by Carlo Baretta on 01/08/2025.
//

#ifndef CONTEXT_H
#define CONTEXT_H
#include "Renderer/OpenGL/OpenGLHeaders.h"
#include "RendererAPI/Camera.h"

/**
 * Context
 * The OpenGL implementation of the renderer context.
 *
 * @param window the active @ref GLFWwindow.
 * @param drawWireframe whether to draw the object in wireframe mode or not.
 * @param backendSpecificContext the backend specific implementation of the renderer context.
 */
typedef struct Context {
    GLFWwindow *window;
    Camera *camera;
    double deltaTime;
    int viewportWidth;
    int viewportHeight;
    bool drawWireframe;
    void *backendSpecificContext;
} Context;

#endif //CONTEXT_H

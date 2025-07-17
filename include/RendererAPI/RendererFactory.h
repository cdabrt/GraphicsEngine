//
// Created by Carlo Baretta on 13/07/2025.
//

#ifndef RENDERERFACTORY_H
#define RENDERERFACTORY_H
#include <GLFW/glfw3.h>

typedef enum {
    OPENGL,
    VULKAN,
} RendererType;

/**
 * createRenderer
 * Creates, initializes and returns a renderer implementation according to the supplied @ref RendererType.
 *
 * @param window the active @ref GLFWwindow
 * @param rendererType the type of renderer implementation @ref RendererType
 */
struct Renderer *createRenderer(GLFWwindow* window,RendererType rendererType);

/**
 * createRendererInjector
 * Creates, initializes and returns a renderer injector according to the supplied @ref RendererType.
 *
 * @param rendererType the type of renderer implementation @ref RendererType
 */
struct RendererInjector *createRendererInjector(RendererType rendererType);

#endif //RENDERERFACTORY_H

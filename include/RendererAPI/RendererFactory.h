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

struct Renderer *createRenderer(GLFWwindow* window,RendererType rendererType);
struct RendererInjector *createRendererInjector(RendererType rendererType);

#endif //RENDERERFACTORY_H

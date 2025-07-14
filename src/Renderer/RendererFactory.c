//
// Created by Carlo Baretta on 13/07/2025.
//

#include "RendererFactory.h"
#include <stdio.h>
#include <stdlib.h>
#include <Renderer/Renderer.h>
#include <Renderer/OpenGL/OpenGLRenderer.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include "OpenGL/OpenGLContext.h"

struct OpenGLContext;

struct Renderer *createRenderer(GLFWwindow* window, const RendererType rendererType) {
struct Renderer *renderer = malloc(sizeof(struct Renderer));
    switch (rendererType) {
        case OPENGL: {
            struct OpenGLContext* openGLContext = malloc(sizeof(*openGLContext));
            memset(openGLContext, 0, sizeof(struct OpenGLContext));
            openGLContext->window = window;

            renderer->initialize = openGLInitialize;
            renderer->render = openGLRender;
            renderer->swapBuffers = openGLSwapBuffers;
            renderer->kill = openGLKill;
            renderer->context = openGLContext;
            break;
        }
        case VULKAN: {
            printf("NOT YET IMPLEMENTED.\n");
            exit(EXIT_FAILURE);
        }
        default: {
            printf("Error: Unknown renderer type.\n");
            exit(EXIT_FAILURE);
        };
    }

    return renderer;
}

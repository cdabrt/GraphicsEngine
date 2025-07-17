//
// Created by Carlo Baretta on 13/07/2025.
//

#include "../../include/RendererAPI/RendererFactory.h"
#include <stdio.h>
#include <stdlib.h>
#include <../include/RendererAPI/Renderer.h>
#include <Renderer/OpenGL/OpenGLRenderer.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include "OpenGL/OpenGLContext.h"
#include "OpenGL/ShaderCompiler/OpenGLInjector.h"

struct OpenGLContext;

struct Renderer *createRenderer(GLFWwindow* window, const RendererType rendererType) {
struct Renderer *renderer = malloc(sizeof(struct Renderer));
    switch (rendererType) {
        case OPENGL: {
            struct OpenGLContext* openGLContext = malloc(sizeof(*openGLContext));
            memset(openGLContext, 0, sizeof(struct OpenGLContext));
            openGLContext->window = window;

            renderer->initialize = openGLInitialize;
            renderer->prepareRenderer = openGLPrepareRender;
            renderer->render = openGLRender;
            renderer->swapBuffers = openGLSwapBuffers;
            renderer->kill = openGLKill;
            renderer->context = openGLContext;
            break;
        }
        case VULKAN: {
            perror("NOT YET IMPLEMENTED.\n");
            exit(EXIT_FAILURE);
        }
        default: {
            perror("Error: Unknown renderer type.\n");
            exit(EXIT_FAILURE);
        };
    }

    return renderer;
}

struct RendererInjector *createRendererInjector(const RendererType rendererType) {
    struct RendererInjector *rendererInjector = malloc(sizeof(struct RendererInjector));
    switch (rendererType) {
        case OPENGL: {
            rendererInjector->createShaderProgram = openGLCreateShaderProgram;
            rendererInjector->setActiveShaderProgram = openGLSetActiveShaderProgram;
            rendererInjector->registerMesh = openGLRegisterMesh;
            break;
        }
        case VULKAN: {
            perror("NOT YET IMPLEMENTED.\n");
            exit(EXIT_FAILURE);
        }
        default: {
            perror("Error: Unknown renderer type.\n");
            exit(EXIT_FAILURE);
        };
    }

    return rendererInjector;
}
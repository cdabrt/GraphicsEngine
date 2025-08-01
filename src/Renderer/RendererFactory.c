//
// Created by Carlo Baretta on 13/07/2025.
//
#include "../../include/RendererAPI/RendererFactory.h"
#include <stdio.h>
#include "Renderer/OpenGL/OpenGLRenderer.h"
#include <string.h>
#include "OpenGL/OpenGLContext.h"
#include "OpenGL/Injector/OpenGLInjector.h"
#include "../include/RendererAPI/Renderer.h"
#include "OpenGL/OpenGLHeaders.h"
#include "../UtilFiles/GeneralErrorHandling.h"
#include "RendererAPI/Context.h"

struct Renderer *createRenderer(GLFWwindow* window, const RendererType rendererType) {
    struct Renderer *renderer = malloc(sizeof(struct Renderer));
    checkMalloc(renderer);
    switch (rendererType) {
        case OPENGL: {
            const int defaultInitValue = 0;

            struct Context *context = malloc(sizeof(struct Context));
            struct OpenGLContext* openGLContext = malloc(sizeof(*openGLContext));
            checkMalloc(openGLContext);
            memset(openGLContext, defaultInitValue, sizeof(struct OpenGLContext));

            context->window = window;
            context->backendSpecificContext = openGLContext;

            renderer->context = context;
            renderer->injector = createRendererInjector(rendererType);
            renderer->prepareRenderer = openGLPrepareRender;
            renderer->render = openGLRender;
            renderer->swapBuffers = openGLSwapBuffers;
            renderer->kill = openGLKill;
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
    checkMalloc(rendererInjector);
    switch (rendererType) {
        case OPENGL: {
            rendererInjector->createShaderProgram = openGLCreateShaderProgram;
            rendererInjector->setActiveShaderProgram = openGLSetActiveShaderProgram;
            rendererInjector->registerMesh = openGLRegisterMesh;
            rendererInjector->getShaderProgramID = openGLGetShaderProgramID;
            rendererInjector->getModel = openGLGetModel;
            rendererInjector->getModelID = openGLGetModelID;
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
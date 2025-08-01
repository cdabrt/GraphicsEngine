//
// Created by Carlo Baretta on 13/07/2025.
//
#include "../../include/RendererAPI/RendererFactory.h"
#include <stdio.h>
#include "Renderer/OpenGL/OpenGLRenderer.h"
#include <string.h>
#include "OpenGL/Context/OpenGLContext.h"
#include "OpenGL/Injector/OpenGLInjector.h"
#include "../include/RendererAPI/Renderer.h"
#include "OpenGL/OpenGLHeaders.h"
#include "../UtilFiles/GeneralErrorHandling.h"
#include "RendererAPI/Context.h"
#include "RendererAPI/Camera.h"

struct Renderer *createRenderer(GLFWwindow* window, const RendererType rendererType) {
    struct Renderer *renderer = malloc(sizeof(struct Renderer));
    checkMalloc(renderer);
    switch (rendererType) {
        case OPENGL: {
            const int defaultInitValue = 0;

            struct Context *context = malloc(sizeof(struct Context));
            checkMalloc(context);

            struct Camera *camera = malloc(sizeof(struct Camera));
            checkMalloc(camera);
            memset(camera, defaultInitValue, sizeof(struct Camera));
            camera->transformation = (struct Transformation) {
                glms_mat4_identity(),
                glms_mat4_identity()
            };

            struct OpenGLContext* openGLContext = malloc(sizeof(*openGLContext));
            checkMalloc(openGLContext);
            memset(openGLContext, defaultInitValue, sizeof(struct OpenGLContext));

            context->window = window;
            context->backendSpecificContext = openGLContext;
            context->camera = camera;
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
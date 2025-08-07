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

Renderer *createRenderer(GLFWwindow* window, const RendererType rendererType) {
    Renderer *renderer = malloc(sizeof(Renderer));
    checkMalloc(renderer);
    switch (rendererType) {
        case OPENGL: {
            const int defaultInitValue = 0;

            Context *context = malloc(sizeof(Context));
            checkMalloc(context);

            Camera *camera = malloc(sizeof(Camera));
            checkMalloc(camera);
            memset(camera, defaultInitValue, sizeof(Camera));
            camera->transformation = (Transformation) {
                glms_mat4_identity(),
                glms_mat4_identity()
            };

            OpenGLContext* openGLContext = malloc(sizeof(*openGLContext));
            checkMalloc(openGLContext);
            memset(openGLContext, defaultInitValue, sizeof(OpenGLContext));

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

RendererInjector *createRendererInjector(const RendererType rendererType) {
    RendererInjector *rendererInjector = malloc(sizeof(RendererInjector));
    checkMalloc(rendererInjector);
    switch (rendererType) {
        case OPENGL: {
            rendererInjector->registerShaderProgram = openGLRegisterShaderProgram;
            rendererInjector->setActiveShaderProgram = openGLSetActiveShaderProgram;
            rendererInjector->registerMesh = openGLRegisterMesh;
            rendererInjector->getShaderProgramID = openGLGetShaderProgramID;
            rendererInjector->getShaderProgram = openGLGetShaderProgram;
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
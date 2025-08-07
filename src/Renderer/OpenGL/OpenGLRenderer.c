//
// Created by Carlo Baretta on 13/07/2025.
//

#include <stdio.h>
#include "OpenGLRenderer.h"
#include "Context/OpenGLContext.h"
#include "ErrorHandling/OpenGLErrorHandling.h"
#include "../../UtilFiles/Macros.h"
#include "Injector/OpenGLInjector.h"
#include "OpenGLHeaders.h"
#include "Window.h"
#include "cglm/struct.h"
#include "RendererAPI/Context.h"
#include "RendererAPI/Renderer.h"
#include "OpenGLTextureRenderer.h"
#include "OpenGLShaderRenderer.h"
#include "OpenGLMeshRenderer.h"

void openGLPrepareRender(Context *context, const int xPos, const int yPos, const int width, const int height) {
    //Initialise GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        perror("Failed to initialize GLAD \n");
        exit(EXIT_FAILURE);
    }

    glViewport(xPos, yPos, width, height);
    CHECK_OPENGL_ERRORS;

    context->viewportWidth = width;
    context->viewportHeight = height;

    prepareShaderRenderer(context);
}

//TODO: See TODO of openGLRegisterMesh.
//TODO: Optimizations such as:
//  material sorting (sort objects that use the same shader and textures to reduce binding calls)
//  batching (add static boolean to mesh. Sort all static meshes together, add them to a single big mesh).
//      Static batches could be updated incrementally if only some static objects change
//      (let's say many houses with doors. The doors do not move most of the time, but occasionally move.
//      If the object moves a lot, it is of course more efficient to flag it as not-static.),
//  texture atlases or arrays,
//  instancing
void openGLRender (const Context *context) {
    OPENGL_CTX;
    const int unbindArray = 0;
    const bool drawWireframe = context->drawWireframe;

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    //TODO: Temporary background colour
    glClearColor(0.4f, 0.5f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLuint activeShaderProgram = openGLContext->activeShaderProgram;
    if (activeShaderProgram == 0) {
        activeShaderProgram = openGLGetShaderProgramID(context, getBaseShaderUniformString(BASE_SHADER));
        openGLSetActiveShaderProgram(context, activeShaderProgram);
    }

    //TODO: Add frustum culling, other types of culling, etc
    if (openGLContext->modelCount > 0) {
        for (int i = 0; i < openGLContext->modelCount; i++) {
            const Model *model = &openGLContext->models[i];
            glBindVertexArray(model->id);

            if (model->shaderProgramID != activeShaderProgram && !context->drawWireframe) {
                openGLSetActiveShaderProgram(context, model->shaderProgramID);
                activeShaderProgram = model->shaderProgramID;
            }

            if (!drawWireframe) {
                bindTextures(model, activeShaderProgram);
            }

            setTransformUniforms(context, model, activeShaderProgram);

            glDrawElements(GL_TRIANGLES, (GLsizei) model->indicesCount, GL_UNSIGNED_INT, NULL);

            if (!drawWireframe) {
                cleanUpRenderer(model);
            }
        }
    }
    glBindVertexArray(unbindArray);
    CHECK_OPENGL_ERRORS;
}



//Poll events and swap front buffer with back buffers
void openGLSwapBuffers (const Context *context) {
    glfwPollEvents();
    glfwSwapBuffers(context->window);
}



void openGLKill (Renderer *renderer) {
    Context *context = renderer->context;
    OPENGL_CTX;
    glFinish();

    killShaders(openGLContext);
    killMeshes(openGLContext);

    free(openGLContext);
    free(renderer->injector);
    free(renderer);

    cleanupWindow(context->window);
    free(context);
}
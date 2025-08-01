//
// Created by Carlo Baretta on 13/07/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "OpenGLRenderer.h"
#include "OpenGLContext.h"
#include "OpenGLErrorHandling.h"
#include "../../UtilFiles/MacrosAndUniforms.h"
#include "Injector/OpenGLInjector.h"
#include "OpenGLHeaders.h"
#include "Window.h"
#include "cglm/struct.h"
#include "RendererAPI/Context.h"
#include "RendererAPI/Renderer.h"

void initializeBaseShaders(struct Context *context, const char* vertexPath, const char* geometryPath,
    const char* fragmentPath, char* shaderName) {
    OPENGL_CTX;
    const char filePathBase[] = "../src/Renderer/OpenGL/Shaders/";
    const unsigned int byteSize = 1024;
    char vertexFullPath[byteSize];
    char fragmentFullPath[byteSize];
    char geometryFullPath[byteSize];

    snprintf(vertexFullPath, sizeof(vertexFullPath), "%s%s", filePathBase, vertexPath);
    snprintf(fragmentFullPath, sizeof(fragmentFullPath), "%s%s", filePathBase, fragmentPath);

    if (geometryPath[0] != '\0') {
        snprintf(geometryFullPath, sizeof(geometryFullPath), "%s%s", filePathBase, geometryPath);
    }

    const GLuint shaderProgram = openGLCreateShaderProgram(vertexFullPath, geometryFullPath, fragmentFullPath);
    registerShaderProgram(openGLContext, shaderProgram, shaderName);

    /*
      The base shader should always be set up before any Model, VBO and EBO setup.
      For macOS this needs to happen immediately after creating the shader programs. Do not move this line somewhere else.
      It would work on Windows, not on macOS.
    */
    openGLSetActiveShaderProgram(context, shaderProgram);
}

void openGLPrepareRender(struct Context *context, const int xPos, const int yPos, const int width, const int height) {
    //Initialise GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        perror("Failed to initialize GLAD \n");
        exit(EXIT_FAILURE);
    }

    glViewport(xPos, yPos, width, height);
    CHECK_OPENGL_ERRORS;

    context->viewportWidth = width;
    context->viewportHeight = height;

    char *vertexPath = "Vertex/vertex_main.vert";
    char *geometryPath = "\0";
    char *fragmentPath = "Fragment/fragment_main.frag";
    BaseShader shader = BASE_SHADER;

    initializeBaseShaders(
    context,
    vertexPath,
    geometryPath,
    fragmentPath,
    getBaseShaderUniformString(shader)
);

    if (context->drawWireframe) {
        vertexPath = "Vertex/vertex_wireframe.vert";
        geometryPath = "\0";
        fragmentPath = "Fragment/fragment_wireframe.frag";
        shader = WIREFRAME_SHADER;
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        CHECK_OPENGL_ERRORS;

        initializeBaseShaders(
            context,
            vertexPath,
            geometryPath,
            fragmentPath,
            getBaseShaderUniformString(shader)
        );
    }
}



void bindTextures(const struct Model *model, const GLuint activeShaderProgram) {
    for (int i = 0; i < model->textureCount; i++) {
        const struct Texture *texture = &model->textures[i];
        glActiveTexture(GL_TEXTURE0 + texture->textureUnit);
        glBindTexture(GL_TEXTURE_2D, texture->id);
        GLint uniformLocation = glGetUniformLocation(activeShaderProgram, texture->uniformName);
        checkUniformLocation(uniformLocation);
        glUniform1i(uniformLocation, texture->textureUnit);
    }
    CHECK_OPENGL_ERRORS;
}



void cleanUpRenderer(const struct Model *model) {
    //Unbind textures
    for (int i = 0; i < model->textureCount; i++) {
        const struct Texture *texture = &model->textures[i];
        glActiveTexture(GL_TEXTURE0 + texture->textureUnit);
        //Texture 0 = "No texture"
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    CHECK_OPENGL_ERRORS;
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
void openGLRender (const struct Context *context) {
    OPENGL_CTX;
    const int unbindArray = 0;
    const bool drawWireframe = context->drawWireframe;

    //TODO: Temporary background colour
    glClearColor(0.4f, 0.5f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint activeShaderProgram = openGLContext->activeShaderProgram;
    if (activeShaderProgram == 0) {
        activeShaderProgram = openGLGetShaderProgramID(context, getBaseShaderUniformString(BASE_SHADER));
        openGLSetActiveShaderProgram(context, activeShaderProgram);
    }

    //TODO: Add frustum culling, other types of culling, etc
    if (openGLContext->modelCount > 0) {
        for (int i = 0; i < openGLContext->modelCount; i++) {
            const struct Model *model = &openGLContext->models[i];
            glBindVertexArray(model->id);

            if (model->shaderProgramID != activeShaderProgram && !context->drawWireframe) {
                openGLSetActiveShaderProgram(context, model->shaderProgramID);
                activeShaderProgram = model->shaderProgramID;
            }

            if (!drawWireframe) {
                bindTextures(model, activeShaderProgram);
            }

            const unsigned int transformUniform = glGetUniformLocation(activeShaderProgram, getBaseMeshUniformString(TRANSFORM));
            checkUniformLocation(transformUniform);
            //TODO: Do not just use local transform. Use world transform as well.
            glUniformMatrix4fv((GLint)transformUniform, 1, GL_FALSE, model->localTransformation->raw[0]);

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
void openGLSwapBuffers (const struct Context *context) {
    glfwPollEvents();
    glfwSwapBuffers(context->window);
}



void openGLKill (struct Renderer *renderer) {
    struct Context *context = renderer->context;
    OPENGL_CTX;
    glFinish();
    cleanupWindow(context->window);

    for (size_t i =0; i < openGLContext->shaderCount; i++) {
        const struct ShaderProgram shaderProgram = openGLContext->shaderPrograms[i];
        glDeleteProgram(shaderProgram.id);
    }

    const int numberOfmodels = 1;
    const int numberOfTexturesToDelete = 1;
    for (size_t i =0; i < openGLContext->modelCount; i++) {
        struct Model *model = &openGLContext->models[i];

        for (int j = 0; j < model->textureCount; j ++) {
            struct Texture *texture = &model->textures[j];
            glDeleteTextures(numberOfTexturesToDelete, &texture->id);
            free(texture->path);
            texture->path = "";
        }
        glDeleteVertexArrays(numberOfmodels, &model->id);

        free(model->localTransformation);
        free(model->worldTransformation);
    }

    CHECK_OPENGL_ERRORS;

    openGLContext->shaderCount = 0;
    openGLContext->modelCount = 0;
    free(openGLContext->shaderPrograms);
    free(openGLContext->models);
    free(openGLContext);
    free(context);
    free(renderer->injector);
    free(renderer);
}
//
// Created by Carlo Baretta on 13/07/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "OpenGLRenderer.h"
#include "OpenGLContext.h"
#include "../../UtilFiles/OpenGLMacrosAndUniforms.h"
#include "Injector/OpenGLInjector.h"
#include "OpenGLHeaders.h"
#include "Window.h"
#include "cglm/struct.h"



void initializeBaseShaders(struct OpenGLContext *openGLContext, const char* vertexPath, const char* geometryPath,
    const char* fragmentPath, char* shaderName) {
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
    addShaderProgram(openGLContext, shaderProgram, shaderName);

    /*
      The base shader should always be set up before any Model, VBO and EBO setup.
      For macOS this needs to happen immediately after creating the shader programs. Do not move this line somewhere else.
      It would work on Windows, not on macOS.
    */
    openGLSetActiveShaderProgram(openGLContext, shaderProgram);
}

void initializeWireframeShaders(struct OpenGLContext *openGLContext) {
    initializeBaseShaders(
        openGLContext,
        "Vertex/vertex_wireframe.vert",
        "\0",
        "Fragment/fragment_wireframe.frag",
        getBaseShaderUniformString(WIREFRAME_SHADER)
        );
}

void openGLInitialize(void *context, const int xPos, const int yPos, const int width, const int height) {
    OPENGL_CTX;

    //Initialise GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        perror("Failed to initialize GLAD \n");
        exit(EXIT_FAILURE);
    }

    glViewport(xPos, yPos, width, height);

    initializeBaseShaders(
        openGLContext,
        "Vertex/vertex_main.vert",
        "\0",
        "Fragment/fragment_main.frag",
        getBaseShaderUniformString(BASE_SHADER)
        );
}



void openGLPrepareRender (void *context, const bool drawWireframe) {
    OPENGL_CTX;

    if (drawWireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        initializeWireframeShaders(openGLContext);
    }
}



void bindTextures(const struct Model *model, const GLuint activeShaderProgram) {
    for (int i = 0; i < model->textureCount; i++) {
        const struct Texture *texture = &model->textures[i];
        glActiveTexture(GL_TEXTURE0 + texture->textureUnit);
        glBindTexture(GL_TEXTURE_2D, texture->id);
        GLint uniformLocation = glGetUniformLocation(activeShaderProgram, texture->uniformName);
        if (uniformLocation == -1) {
            printf("Uniform does not exist");
        }
        glUniform1i(uniformLocation, texture->textureUnit);
    }
}

void cleanUpRenderer(const struct Model *model) {
    //Unbind textures
    for (int i = 0; i < model->textureCount; i++) {
        const struct Texture *texture = &model->textures[i];
        glActiveTexture(GL_TEXTURE0 + texture->textureUnit);
        //Texture 0 = "No texture"
        glBindTexture(GL_TEXTURE_2D, 0);
    }
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
void openGLRender (void *context, const bool drawWireframe) {
    OPENGL_CTX;
    const int array = 0;

    //TODO: Temporary background colour
    glClearColor(0.4f, 0.5f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint activeShaderProgram = openGLContext->activeShaderProgram;
    if (activeShaderProgram == 0) {
        activeShaderProgram = getShaderProgramID(openGLContext, getBaseShaderUniformString(BASE_SHADER));
        openGLSetActiveShaderProgram(context, activeShaderProgram);
    }

    //TODO: Add frustum culling, other types of culling, etc
    if (openGLContext->modelCount > 0) {
        for (int i = 0; i < openGLContext->modelCount; i++) {
            const struct Model *model = &openGLContext->models[i];
            glBindVertexArray(model->id);

            if (model->shaderProgramID != activeShaderProgram) {
                openGLSetActiveShaderProgram(context, model->shaderProgramID);
                activeShaderProgram = model->shaderProgramID;
            }

            if (!drawWireframe) {
                bindTextures(model, activeShaderProgram);
            }

            //------------------------------------------------------------------------------------------

            //TODO: Testing, this has to be somewhere else.
            //  Maybe a mesh function. Perhaps we can make another abstraction on top of ModelModel. A GameObject has a ModelModel.
            //  So we have RawMesh -> Texture. (The RawMesh struct is only used as a DTO for using the vertex data in the registration of a ModelModel)
            //  and
            //  GameObject -> ModelModel (dependency on RawMesh for meshdata and textures) -> Texture * -> ShaderProgram (ID, sort of primary key relation)
            mat4s transformation = glms_mat4_identity();
            transformation = glms_rotate(transformation, glm_rad(90.0f), (vec3s){ .x = 0.0f, .y = 0.0f, .z = 1.0f });
            transformation = glms_scale(transformation, (vec3s){ .x = 0.5f, .y = 0.5f, .z = 0.5f});

            const unsigned int transformLoc = glGetUniformLocation(activeShaderProgram, getBaseMeshUniformString(TRANSFORM));
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transformation.raw[0]);

            //------------------------------------------------------------------------------------------

            glDrawElements(GL_TRIANGLES, (GLsizei) model->indicesCount, GL_UNSIGNED_INT, NULL);

            if (!drawWireframe) {
                cleanUpRenderer(model);
            }
        }
    }
    glBindVertexArray(array);
}



//Poll events and swap front buffer with back buffers
void openGLSwapBuffers (void *context) {
    OPENGL_CTX;
    glfwPollEvents();
    glfwSwapBuffers(openGLContext->window);
}



void openGLKill (void *context) {
    OPENGL_CTX;
    glFinish();
    cleanupWindow(openGLContext->window);

    for (size_t i =0; i < openGLContext->shaderCount; i++) {
        const struct ShaderProgram shaderProgram = openGLContext->shaderPrograms[i];
        glDeleteProgram(shaderProgram.id);
    }

    const int numberOfmodels = 1;
    const int numberOfTexturesToDelete = 1;
    for (size_t i =0; i < openGLContext->modelCount; i++) {
        const struct Model *model = &openGLContext->models[i];

        for (int j = 0; j < model->textureCount; j ++) {
            struct Texture *texture = &model->textures[j];
            glDeleteTextures(numberOfTexturesToDelete, &texture->id);
            free(texture->path);
            texture->path = "";
        }
        glDeleteVertexArrays(numberOfmodels, &model->id);
    }

    openGLContext->shaderCount = 0;
    openGLContext->modelCount = 0;
    free(openGLContext->shaderPrograms);
    free(openGLContext->models);
    free(openGLContext);
}
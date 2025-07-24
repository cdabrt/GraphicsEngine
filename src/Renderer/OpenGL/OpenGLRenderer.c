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

    /*The base shader should always be set up before any VAO, VBO and EBO setup.
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



//TODO: See TODO of openGLRegisterMesh.
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
    if (openGLContext->vaoCount > 0) {
        for (int i = 0; i < openGLContext->vaoCount; i++) {
            const struct VAO *vao = &openGLContext->vaos[i];
            glBindVertexArray(vao->id);

            if (vao->shaderProgramID != activeShaderProgram) {
                openGLSetActiveShaderProgram(context, vao->shaderProgramID);
                activeShaderProgram = vao->shaderProgramID;
            }

            if (!drawWireframe) {
                for (int j = 0; j < vao->textureCount; j++) {
                    const struct Texture *texture = &vao->textures[j];
                    glActiveTexture(GL_TEXTURE0 + texture->textureUnit);
                    glBindTexture(GL_TEXTURE_2D, texture->id);
                    if (glGetUniformLocation(activeShaderProgram, texture->uniformName) == -1) {
                        printf("Uniform does not exist");
                    }
                    glUniform1i(glGetUniformLocation(activeShaderProgram, texture->uniformName), texture->textureUnit);
                }
            }

            // glm::mat4 trans = glm::mat4(1.0f);
            // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
            // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
            //
            // unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
            // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

            glDrawElements(GL_TRIANGLES, (GLsizei) vao->indicesCount, GL_UNSIGNED_INT, NULL);
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

    const int numberOfVAOs = 1;
    const int numberOfTexturesToDelete = 1;
    for (size_t i =0; i < openGLContext->vaoCount; i++) {
        const struct VAO *vao = &openGLContext->vaos[i];

        for (int j = 0; j < vao->textureCount; j ++) {
            struct Texture *texture = &vao->textures[j];
            glDeleteTextures(numberOfTexturesToDelete, &texture->id);
            free(texture->path);
            texture->path = "";
        }
        glDeleteVertexArrays(numberOfVAOs, &vao->id);
    }

    openGLContext->shaderCount = 0;
    openGLContext->vaoCount = 0;
    free(openGLContext->shaderPrograms);
    free(openGLContext->vaos);
    free(openGLContext);
}
//
// Created by Carlo Baretta on 01/08/2025.
//

#include <stdio.h>
#include <string.h>
#include "../Context/OpenGLContext.h"
#include "../../../UtilFiles/Macros.h"
#include "../Injector/OpenGLInjector.h"
#include "../OpenGLHeaders.h"
#include "../ErrorHandling/OpenGLErrorHandling.h"
#include "RendererAPI/BaseUniforms.h"
#include "RendererAPI/Context.h"
#include "RendererAPI/Renderer.h"
#include "UtilFiles/GeneralErrorHandling.h"

void updateBDOs(const Context *context, const ShaderProgram *activeShaderProgram) {
    for (int i = 0; i < activeShaderProgram->uboCount; i ++) {
        UBO *ubo = &activeShaderProgram->ubos[i];

        //TODO: I know for a fact the ubo->data is not updating. That's why this is here for now
        // CameraBlock *cameraBlock = (CameraBlock*)ubo->data;
        //
        // memcpy(cameraBlock->perspective, context->camera->perspective.raw, sizeof(float) * 16);
        // memcpy(cameraBlock->view, context->camera->view.raw, sizeof(float) * 16);

        glBindBuffer(GL_UNIFORM_BUFFER, ubo->id);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(ubo->data), ubo->data);
    }
}

void initializeBaseUBOs(Context *context, unsigned int shaderProgramID) {
    ShaderProgram *shaderProgram = openGLGetShaderProgram(context, shaderProgramID);

    //Initialize camera UBO data
    const unsigned int cameraBlockSize = sizeof(CameraBlock);
    const unsigned int matrixSize = sizeof(float[16]);
    const GLuint uboID = openGLRegisterUBO(shaderProgram->id, cameraBlockSize);

    const Camera *camera = context->camera;
    CameraBlock *cameraBlock = malloc(cameraBlockSize);
    checkMalloc(cameraBlock);
    memcpy(cameraBlock->perspective, camera->perspective.raw, matrixSize);
    memcpy(cameraBlock->view, camera->view.raw, matrixSize);

    registerUBO(
        shaderProgram,
        getBaseBlockUniformString(CAMERA_VIEW),
        uboID,
        getBaseBlockUniformBinding(CAMERA_VIEW),
        cameraBlockSize,
        cameraBlock
        );
}

void initializeBaseShaders(Context *context, const char* vertexPath, const char* geometryPath,
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

    const GLuint shaderProgramID = openGLRegisterShaderProgram(vertexFullPath, geometryFullPath, fragmentFullPath);
    registerShaderProgram(openGLContext, shaderProgramID, shaderName);

    initializeBaseUBOs(context, shaderProgramID);

    /*
      The base shader should always be set up before any Model, VBO and EBO setup.
      For macOS this needs to happen immediately after creating the shader programs. Do not move this line somewhere else.
      It would work on Windows, not on macOS.
    */
    openGLSetActiveShaderProgram(context, shaderProgramID);
}


void prepareShaderRenderer(Context *context) {
    char *vertexPath = "Vertex/vertex_main.vert";
    char *geometryPath = "\0";
    char *fragmentPath = "Fragment/fragment_main.frag";
    BaseShader shader = BASE_SHADER;

    initializeBaseShaders(
        context,
        vertexPath,
        geometryPath,
        fragmentPath,
        getBaseShaderString(shader)
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
            getBaseShaderString(shader)
        );
    }
}

void killShaders(OpenGLContext *openGLContext) {
    glUseProgram(0);
    for (size_t i =0; i < openGLContext->shaderCount; i++) {
        const ShaderProgram shaderProgram = openGLContext->shaderPrograms[i];

        for (size_t j =0; j < shaderProgram.uboCount; j++) {
            const UBO *ubo = &shaderProgram.ubos[j];
            glDeleteBuffers(1, &ubo->id);
            free(ubo->data);
        }

        glDeleteProgram(shaderProgram.id);
    }

    openGLContext->shaderCount = 0;
    free(openGLContext->shaderPrograms);
    CHECK_OPENGL_ERRORS;
}
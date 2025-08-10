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

void updateUBOs(const Context *context, const ShaderProgram *activeShaderProgram) {
    for (int i = 0; i < activeShaderProgram->uboCount; i ++) {
        UBO *ubo = &activeShaderProgram->ubos[i];

        //If this is the camera data UBO. For every context that has a camera, a shader program can access the camera data.
        if (ubo->uniformBlockBindingIndex == getBaseBlockUniformBinding(CAMERA_VIEW)) {
            const unsigned int matrixSize = sizeof(float[16]);
            Camera *camera = context->camera;
            CameraBlock *cameraBlock = (CameraBlock *)ubo->data;
            memcpy(cameraBlock->perspective, camera->perspective.raw, matrixSize);
            memcpy(cameraBlock->view, camera->view.raw, matrixSize);
        }

        glBindBuffer(GL_UNIFORM_BUFFER, ubo->id);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, ubo->bufferSize, ubo->data);
        glBindBufferBase(GL_UNIFORM_BUFFER, ubo->uniformBlockBindingIndex, ubo->id);
    }

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void updateActiveShaderProgram(const Model *model, const Context *context, unsigned int *activeShaderProgram, const bool drawWireframe) {
    const unsigned int wireFrameID = openGLGetShaderProgramID(context, getBaseShaderString(WIREFRAME_SHADER));

    if (model->shaderProgramID != *activeShaderProgram && !drawWireframe) {
        openGLSetActiveShaderProgram(context, model->shaderProgramID);
        *activeShaderProgram = model->shaderProgramID;

        glEnable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glClear(GL_DEPTH_BUFFER_BIT);

        updateUBOs(context, openGLGetShaderProgram(context, *activeShaderProgram));
    } else if (drawWireframe && *activeShaderProgram != wireFrameID) {
        openGLSetActiveShaderProgram(context,wireFrameID);
        *activeShaderProgram = wireFrameID;
        updateUBOs(context, openGLGetShaderProgram(context, *activeShaderProgram));

        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glClear(GL_DEPTH_BUFFER_BIT);
    }
}

void initializeBaseUBOs(Context *context, unsigned int shaderProgramID) {
    ShaderProgram *shaderProgram = openGLGetShaderProgram(context, shaderProgramID);

    //Initialize camera UBO data
    const unsigned int cameraBlockSize = sizeof(CameraBlock);
    const GLuint uboID = openGLRegisterUBO(shaderProgram->id, cameraBlockSize);

    CameraBlock *cameraBlock = malloc(cameraBlockSize);
    checkMalloc(cameraBlock);
    memset(cameraBlock, 0, sizeof(CameraBlock));

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
    char *vertexPath = "Vertex/vertex_wireframe.vert";
    char *geometryPath = "\0";
    char *fragmentPath = "Fragment/fragment_wireframe.frag";
    BaseShader shader = WIREFRAME_SHADER;

    initializeBaseShaders(
        context,
        vertexPath,
        geometryPath,
        fragmentPath,
        getBaseShaderString(shader)
    );

    vertexPath = "Vertex/vertex_main.vert";
    geometryPath = "\0";
    fragmentPath = "Fragment/fragment_main.frag";
    shader = BASE_SHADER;

    initializeBaseShaders(
        context,
        vertexPath,
        geometryPath,
        fragmentPath,
        getBaseShaderString(shader)
    );
}

void killShaders(OpenGLContext *openGLContext) {
    glUseProgram(0);
    for (size_t i =0; i < openGLContext->shaderCount; i++) {
        const ShaderProgram *shaderProgram = &openGLContext->shaderPrograms[i];

        for (size_t j =0; j < shaderProgram->uboCount; j++) {
            const UBO *ubo = &shaderProgram->ubos[j];
            glDeleteBuffers(1, &ubo->id);
            free(ubo->data);
        }
        free(shaderProgram->ubos);

        glDeleteProgram(shaderProgram->id);
    }

    openGLContext->shaderCount = 0;
    free(openGLContext->shaderPrograms);
    CHECK_OPENGL_ERRORS;
}
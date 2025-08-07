//
// Created by Carlo Baretta on 01/08/2025.
//

#include <stdio.h>
#include "../Context/OpenGLContext.h"
#include "../../../UtilFiles/Macros.h"
#include "../Injector/OpenGLInjector.h"
#include "../OpenGLHeaders.h"
#include "../ErrorHandling/OpenGLErrorHandling.h"
#include "RendererAPI/Context.h"
#include "RendererAPI/Renderer.h"

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

    const GLuint shaderProgram = openGLCreateShaderProgram(vertexFullPath, geometryFullPath, fragmentFullPath);
    registerShaderProgram(openGLContext, shaderProgram, shaderName);

    /*
      The base shader should always be set up before any Model, VBO and EBO setup.
      For macOS this needs to happen immediately after creating the shader programs. Do not move this line somewhere else.
      It would work on Windows, not on macOS.
    */
    openGLSetActiveShaderProgram(context, shaderProgram);
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
        glDeleteProgram(shaderProgram.id);
    }

    openGLContext->shaderCount = 0;
    free(openGLContext->shaderPrograms);
    CHECK_OPENGL_ERRORS;
}
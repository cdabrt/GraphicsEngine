//
// Created by Carlo Baretta on 01/08/2025.
//

#ifndef OPENGLSHADERRENDERER_H
#define OPENGLSHADERRENDERER_H

#include "RendererAPI/Context.h"

void initializeBaseShaders(struct Context *context, const char* vertexPath, const char* geometryPath,
    const char* fragmentPath, char* shaderName);

void prepareShaderRenderer(struct Context *context);

void killShaders(struct OpenGLContext *openGLContext);

#endif //OPENGLSHADERRENDERER_H

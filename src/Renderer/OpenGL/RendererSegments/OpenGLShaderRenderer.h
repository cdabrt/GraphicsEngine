//
// Created by Carlo Baretta on 01/08/2025.
//

#ifndef OPENGLSHADERRENDERER_H
#define OPENGLSHADERRENDERER_H

#include "RendererAPI/Context.h"

void updateUBOs(const Context *context, const ShaderProgram *activeShaderProgram);

void updateActiveShaderProgram(const Model *model, const Context *context, unsigned int *activeShaderProgram, bool drawWireframe);

void initializeBaseShaders(Context *context, const char* vertexPath, const char* geometryPath,
                           const char* fragmentPath, char* shaderName);

void prepareShaderRenderer(Context *context);

void killShaders(OpenGLContext *openGLContext);

#endif //OPENGLSHADERRENDERER_H

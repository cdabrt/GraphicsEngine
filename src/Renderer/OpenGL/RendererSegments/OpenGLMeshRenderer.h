//
// Created by Carlo Baretta on 01/08/2025.
//

#ifndef OPENGLMESHRENDERER_H
#define OPENGLMESHRENDERER_H

void updateBDOs(const Context *context, const ShaderProgram *activeShaderProgram);

void setTransformUniforms(const Model *model, unsigned int activeShaderProgram);

void killMeshes(OpenGLContext *openGLContext);

#endif //OPENGLMESHRENDERER_H

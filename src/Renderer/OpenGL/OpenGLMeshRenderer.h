//
// Created by Carlo Baretta on 01/08/2025.
//

#ifndef OPENGLMESHRENDERER_H
#define OPENGLMESHRENDERER_H

void setTransformUniforms(const struct Context *context, const struct Model *model, unsigned int activeShaderProgram);

void killMeshes(struct OpenGLContext *openGLContext);

#endif //OPENGLMESHRENDERER_H

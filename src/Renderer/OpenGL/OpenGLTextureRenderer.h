//
// Created by Carlo Baretta on 01/08/2025.
//

#include "Context/OpenGLContext.h"
#include "OpenGLHeaders.h"

#ifndef TEXTURERENDERER_H
#define TEXTURERENDERER_H

void bindTextures(const struct Model *model, GLuint activeShaderProgram);

void cleanUpRenderer(const struct Model *model);

void killTextures(struct Model *model);

#endif //TEXTURERENDERER_H

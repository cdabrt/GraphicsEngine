//
// Created by Carlo Baretta on 01/08/2025.
//

#include "Context/OpenGLContext.h"
#include "OpenGLHeaders.h"

#ifndef TEXTURERENDERER_H
#define TEXTURERENDERER_H

void bindTextures(const Model *model, GLuint activeShaderProgram);

void cleanUpRenderer(const Model *model);

void killTextures(Model *model);

#endif //TEXTURERENDERER_H

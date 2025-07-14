//
// Created by Carlo Baretta on 14/07/2025.
//

#ifndef OPENGLSHADERINJECTOR_H
#define OPENGLSHADERINJECTOR_H
#include "glad/Glad.h"

GLuint createShaderProgram(char *vertexFilePath, char *fragmentFilePath);
void setActiveShaderProgram(void *context, GLuint programId);

#endif //OPENGLSHADERINJECTOR_H

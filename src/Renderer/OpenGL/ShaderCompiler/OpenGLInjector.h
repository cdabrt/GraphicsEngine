//
// Created by Carlo Baretta on 14/07/2025.
//

#ifndef OPENGLSHADERINJECTOR_H
#define OPENGLSHADERINJECTOR_H

unsigned int openGLCreateShaderProgram(char *vertexFilePath, char *fragmentFilePath);
void openGLSetActiveShaderProgram(void *context, GLuint programId);
unsigned int openGLRegisterMesh(void *context, const float *vertices, const int *indices, long vertexDataSize, long indicesDataSize);

#endif //OPENGLSHADERINJECTOR_H

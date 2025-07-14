//
// Created by Carlo Baretta on 13/07/2025.
//

#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

GLuint createShaderProgram(char *vertexFilePath, char *fragmentFilePath);
void setActiveShaderProgram(void *context, GLuint programId);

void openGLInitialize(void *context, int xPos, int yPos, int width, int height);
unsigned int openGLPrepareRender (const float *vertices, const float *indices,
    long vertexDataSize, long indicesDataSize, bool drawWireframe);
void openGLRender (void *context, unsigned int VAO, const long indicesCount);
void openGLSwapBuffers (void *context);
void openGLKill (void *context);

#endif //OPENGLRENDERER_H

//
// Created by Carlo Baretta on 13/07/2025.
//

#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

GLuint createShaderProgram(char *vertexFilePath, char *fragmentFilePath);
void setActiveShaderProgram(void *context, GLuint programId);

void openGLInitialize(void *context, int xPos, int yPos, int width, int height);
void openGLRender (void *context, float vertices[]);
void openGLSwapBuffers (void *context);
void openGLKill (void *context);

#endif //OPENGLRENDERER_H

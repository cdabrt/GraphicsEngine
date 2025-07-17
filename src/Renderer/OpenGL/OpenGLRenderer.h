//
// Created by Carlo Baretta on 13/07/2025.
//

#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

void openGLInitialize(void *context, int xPos, int yPos, int width, int height);
void openGLPrepareRender (bool drawWireframe);
void openGLRender (void *context);
void openGLSwapBuffers (void *context);
void openGLKill (void *context);

#endif //OPENGLRENDERER_H

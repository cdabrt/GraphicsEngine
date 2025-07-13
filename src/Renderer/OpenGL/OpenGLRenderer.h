//
// Created by Carlo Baretta on 13/07/2025.
//

#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H
#include "GLFW/glfw3.h"

struct OpenGLContext {
    GLFWwindow* window;
};

void openGLInitialize(int xPos, int yPos, int width, int height);
void openGLRender (void *context, float vertices[]);
void openGLSwapBuffers (void *context);

#endif //OPENGLRENDERER_H

//
// Created by Carlo Baretta on 13/07/2025.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

void glfwWindowSetup();

GLFWwindow* createWindow(int width, int height);

void cleanupWindow(GLFWwindow* window);

#endif //WINDOW_H

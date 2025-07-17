//
// Created by Carlo Baretta on 13/07/2025.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

/**
 * glfwWindowSetup
 * Setup function for glfw.
 */
void glfwWindowSetup();

/**
 * createWindow
 * Creates a @ref GLFWwindow instance.
 *
 * @param width initial width of the window
 * @param height initial height of the window
 */
GLFWwindow* createWindow(int width, int height);

/**
 * cleanupWindow
 * Creates a @ref GLFWwindow instance.
 *
 * @param window the to be destroyed active @ref GLFWwindow
 */
void cleanupWindow(GLFWwindow* window);

#endif //WINDOW_H

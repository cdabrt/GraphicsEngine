//
// Created by Carlo Baretta on 13/07/2025.
//

#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H
#include "RendererAPI/Renderer.h"

/**
 * processWindowInput
 * Processes keybord inputs made within a @ref GLFWwindow instance.
 *
 * @param renderer the @ref Renderer.
 */
void processWindowInput(const Renderer *renderer);

/**
 * moveCamera
 * Move the camera according to keyboard inputs.
 *
 * @param renderer the @ref Renderer.
 * @param window the window.
 */
void moveCamera(const Renderer *renderer, GLFWwindow *window);

void mouseCallback(GLFWwindow* window, double xPos, double yPos);

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void mousePressCallback(GLFWwindow* window, int key, int action, int mods);

#endif //INPUTCONTROLLER_H

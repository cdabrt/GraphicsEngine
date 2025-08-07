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

void mouse_callback(GLFWwindow* window, double xPos, double yPos);

#endif //INPUTCONTROLLER_H

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
void processWindowInput(const struct Renderer *renderer);

#endif //INPUTCONTROLLER_H

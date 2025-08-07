//
// Created by Carlo Baretta on 13/07/2025.
//

#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "RendererAPI/Context.h"
#include "RendererAPI/Renderer.h"

/**
 * openGLPrepareRender
 * Initializes OpenGL.
 *
 * @param context @ref OpenGLContext.
 * @param xPos x position of the viewport.
 * @param yPos y position of the viewport.
 * @param width width of the viewport.
 * @param height height of the viewport.
 *
 * @note The viewport can be made smaller than the actual @ref GLFWwindow,
 * so that you can use for example native UI elements around the smaller viewport that renders the OpenGL graphics.
 */
void openGLPrepareRender(Context *context, int xPos, int yPos, int width, int height);

/**
 * openGLRender
 * The renderer loop of the OpenGL renderer implementation.
 *
 * @param context @ref OpenGLContext.
 */
void openGLRender (const Context *context);

/**
 * openGLSwapBuffers
 * Swaps the front buffer with the back buffers.
 *
 * @param context @ref OpenGLContext.
 */
void openGLSwapBuffers (const Context *context);

/**
 * openGLKill
 * Kills all OpenGL processes and frees all @ref Renderer and @ref OpenGLContext related memory allocations
 *
 * @param renderer @ref OpenGLContext.
 */
void openGLKill (Renderer *renderer);

#endif //OPENGLRENDERER_H

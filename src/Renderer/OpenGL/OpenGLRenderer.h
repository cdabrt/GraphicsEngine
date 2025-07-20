//
// Created by Carlo Baretta on 13/07/2025.
//

#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

/**
 * openGLInitialize
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
void openGLInitialize(void *context, int xPos, int yPos, int width, int height);

/**
 * openGLPrepareRender
 * Prepares the OpenGL renderer implementation.
 *
 * @param drawWireframe should the meshes be drawn in wireframe mode (TRUE OR FALSE).
 */
void openGLPrepareRender (bool drawWireframe);

/**
 * openGLRender
 * The renderer loop of the OpenGL renderer implementation.
 *
 * @param context @ref OpenGLContext.
 */
void openGLRender (void *context);

/**
 * openGLSwapBuffers
 * Swaps the front buffer with the back buffers.
 *
 * @param context @ref OpenGLContext.
 */
void openGLSwapBuffers (void *context);

/**
 * openGLKill
 * Kills all OpenGL processes and frees all @ref OpenGLContext related memory allocations
 *
 * @param context @ref OpenGLContext.
 */
void openGLKill (void *context);

#endif //OPENGLRENDERER_H

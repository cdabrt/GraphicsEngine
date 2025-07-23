//
// Created by carlo on 17-7-2025.
//

#ifndef OPENGLMACROS_H
#define OPENGLMACROS_H
#include <Renderer/OpenGL/OpenGLContext.h>

/**
 * OPENGL_CTX
 * Declares and initializes a pointer to the OpenGL rendering context implementation.
 *
 * @param context the renderer context.
 *
 * @note This macro implicitly creates a variable called `openGLContext`. Use carefully to avoid naming conflicts.
 *
 * \b Expands to:
 * @code
 *      struct OpenGLContext *openGLContext = (struct OpenGLContext *)context;
 * @endcode
 *
 * \b Usage:
 * @code
 *      void someOpenGLFunction(void *context) {
 *          OPENGL_CTX; // Now you can use `openGLContext`
 *           ...
 *      }
 * @endcode
 */
#define OPENGL_CTX struct OpenGLContext *openGLContext = (struct OpenGLContext *)context

#define BASE_SHADER "baseShader"

#define WIREFRAME_SHADER "wireframeShader"

#endif //OPENGLMACROS_H

//
// Created by carlo on 17-7-2025.
//

#ifndef OPENGLMACROS_H
#define OPENGLMACROS_H
#include <stdio.h>
#include <Renderer/OpenGL/Context/OpenGLContext.h>

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
 *      OpenGLContext *openGLContext = (struct OpenGLContext *)context;
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
#define OPENGL_CTX OpenGLContext *openGLContext = (OpenGLContext *)context->backendSpecificContext


#endif //OPENGLMACROS_H

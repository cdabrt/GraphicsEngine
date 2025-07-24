//
// Created by Carlo Baretta on 13/07/2025.
//

#ifndef RENDERINGSTRATEGY_H
#define RENDERINGSTRATEGY_H

#include "RendererAPI/RawMesh.h"

typedef void (*InitializeFunction) (void *context, int xPos, int yPos, int width, int height);
typedef void (*PrepareRendererFunction) (void *context, bool drawWireframe);
typedef void (*RenderFunction) (void *context, bool drawWireframe);
typedef void (*SwapBuffersFunction) (void *context);
typedef void (*KillFunction) (void *context);

/**
 * Renderer
 * An abstraction for the different renderer implementations. Specific implementations of the functions
 * that are pointed to within the struct are supplied in @ref createRenderer.
 *
 * @param context the renderer context.
 * @param initialize the initialization function.
 * @param prepareRenderer the prepareRenderer function.
 * @param render the render function.
 * @param swapBuffers the swapBuffers function.
 * @param kill the kill function.
 */
struct Renderer {
    //pointer to instance-specific data or "context"
    void *context;
    InitializeFunction initialize;
    PrepareRendererFunction prepareRenderer;
    RenderFunction render;
    SwapBuffersFunction swapBuffers;
    KillFunction kill;
};



typedef unsigned int (*CreateShaderProgramFunction) (char *vertexFilePath, char *geometryFilePath, char *fragmentFilePath);
typedef void (*SetActiveShaderProgramFunction) (void *context, unsigned long programId);
typedef unsigned int (*RegisterMeshFunction) (void *context, const struct RawMesh *mesh, unsigned long shaderProgramID);

/**
 * RendererInjector
 * An abstraction for the different renderer injection implementations. Specific implementations of the functions
 * that are pointed to within the struct are supplied in @ref createRendererInjector.
 *
 * @param createShaderProgram the createShaderProgram function
 * @param setActiveShaderProgram the setActiveShaderProgram function
 * @param registerMesh the registerMesh function. Returns the ID of the created VAO
 */
struct RendererInjector {
    CreateShaderProgramFunction createShaderProgram;
    SetActiveShaderProgramFunction setActiveShaderProgram;
    RegisterMeshFunction registerMesh;
};

/**
 * RendererInjector
 * An abstraction for the different renderer injection implementations. Specific implementations of the functions
 * that are pointed to within the struct are supplied in @ref createRendererInjector.
 *
 * @param current the current renderer implementation
 * @param new the new renderer implementation
 *
 * \b Usage:
 * @code
 *      swapRenderer(&currentRenderer, &newRenderer);
 * @endcode
 */
void swapRenderer(struct Renderer **current, const struct Renderer *new);

#endif //RENDERINGSTRATEGY_H

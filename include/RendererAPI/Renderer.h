//
// Created by Carlo Baretta on 13/07/2025.
//

#ifndef RENDERINGSTRATEGY_H
#define RENDERINGSTRATEGY_H

#include "RendererAPI/RawMesh.h"
#include "RendererAPI/Context.h"

typedef unsigned int (*CreateShaderProgramFunction) (char *vertexFilePath, char *geometryFilePath, char *fragmentFilePath);
typedef void (*SetActiveShaderProgramFunction) (const struct Context *context, unsigned long programId);
typedef unsigned int (*RegisterMeshFunction) (const struct Context *context, const struct RawMesh *mesh, char *modelName, unsigned long shaderProgramID);
typedef unsigned int (*getShaderProgramIdFunction) (const struct Context *context, const char *shaderName);
typedef struct Model *(*getModelFunction) (const struct Context *context, unsigned int modelID);
typedef unsigned int (*getModelIDFunction) (const struct Context *context, const char *meshName);

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
    getShaderProgramIdFunction getShaderProgramID;
    getModelFunction getModel;
    getModelIDFunction getModelID;
};

typedef void (*PrepareRendererFunction) (struct Context *context, int xPos, int yPos, int width, int height);
typedef void (*RenderFunction) (const struct Context *context);
typedef void (*SwapBuffersFunction) (const struct Context *context);
typedef void (*KillFunction) (struct Renderer *renderer);

/**
 * Renderer
 * An abstraction for the different renderer implementations. Specific implementations of the functions
 * that are pointed to within the struct are supplied in @ref createRenderer.
 *
 * @param context the renderer context.
 * @param injector the renderer injector.
 * @param initialize the initialization function.
 * @param prepareRenderer the prepareRenderer function.
 * @param render the render function.
 * @param swapBuffers the swapBuffers function.
 * @param kill the kill function.
 */
struct Renderer {
    struct Context *context;
    struct RendererInjector *injector;
    PrepareRendererFunction prepareRenderer;
    RenderFunction render;
    SwapBuffersFunction swapBuffers;
    KillFunction kill;
};



/**
 * swapRenderer
 * Swap the renderer with a new instance
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

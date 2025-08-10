//
// Created by Carlo Baretta on 13/07/2025.
//

#ifndef RENDERINGSTRATEGY_H
#define RENDERINGSTRATEGY_H

#include "RendererAPI/RawMesh.h"
#include "RendererAPI/Context.h"

typedef enum {
    BASE_SHADER,
    WIREFRAME_SHADER,
} BaseShader;

inline char *getBaseShaderString(const BaseShader shader)
{
    char *string = "\0";

    switch(shader) {
        case BASE_SHADER: string="baseShader"; break;
        case WIREFRAME_SHADER: string="wireframeShader"; break;
        default:
            perror("Unknown shader type");
    }

    return string;
}

typedef unsigned int (*RegisterShaderProgramFunction) (char *vertexFilePath, char *geometryFilePath, char *fragmentFilePath);
typedef void (*SetActiveShaderProgramFunction) (const Context *context, unsigned int programId);
typedef unsigned int (*RegisterMeshFunction) (const Context *context, const RawMesh *mesh, char *modelName, unsigned int shaderProgramID);
typedef unsigned int (*getShaderProgramIdFunction) (const Context *context, const char *shaderName);
typedef ShaderProgram *(*getShaderProgramFunction) (const Context *context, unsigned int shaderProgramID);
typedef Model *(*getModelFunction) (const Context *context, unsigned int modelID);
typedef unsigned int (*getModelIDFunction) (const Context *context, const char *meshName);

/**
 * RendererInjector
 * An abstraction for the different renderer injection implementations. Specific implementations of the functions
 * that are pointed to within the struct are supplied in @ref createRendererInjector.
 *
 * @param createShaderProgram the createShaderProgram function
 * @param setActiveShaderProgram the setActiveShaderProgram function
 * @param registerMesh the registerMesh function. Returns the ID of the created VAO
 */
typedef struct RendererInjector {
    RegisterShaderProgramFunction registerShaderProgram;
    SetActiveShaderProgramFunction setActiveShaderProgram;
    RegisterMeshFunction registerMesh;
    getShaderProgramIdFunction getShaderProgramID;
    getShaderProgramFunction getShaderProgram;
    getModelFunction getModel;
    getModelIDFunction getModelID;
} RendererInjector;

typedef struct Renderer Renderer;
typedef void (*PrepareRendererFunction) (Context *context, int xPos, int yPos, int width, int height);
typedef void (*RenderFunction) (const Context *context);
typedef void (*SwapBuffersFunction) (const Context *context);
typedef void (*KillFunction) (Renderer *renderer);

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
 *
 * @note \b Be \b careful! Every time you switch the context of the renderer, make sure to run prepareRenderer.
 * This way, the base shaders and UBOs can be prepared in the new context.
 */
struct Renderer {
    Context *context;
    RendererInjector *injector;
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
void swapRenderer(Renderer **current, const Renderer *new);

#endif //RENDERINGSTRATEGY_H

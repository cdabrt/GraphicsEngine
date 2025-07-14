//
// Created by Carlo Baretta on 13/07/2025.
//

#ifndef RENDERINGSTRATEGY_H
#define RENDERINGSTRATEGY_H

typedef void (*InitializeFunction) (void *context, int xPos, int yPos, int width, int height);
typedef unsigned int (*PrepareRendererFunction) (const float *vertices, const float *indices,
    long vertexDataSize, long indicesDataSize, bool drawWireframe);
typedef void (*RenderFunction) (void *context, unsigned int VAO, long indicesCount);
typedef void (*SwapBuffersFunction) (void *context);
typedef void (*KillFunction) (void *context);


struct Renderer {
    //pointer to instance-specific data or "context"
    void *context;
    InitializeFunction initialize;
    PrepareRendererFunction prepareRenderer;
    RenderFunction render;
    SwapBuffersFunction swapBuffers;
    KillFunction kill;
};

//usage: swapRenderer(&currentRenderer, &newRenderer);
void swapRenderer(struct Renderer **current, const struct Renderer *new);

#endif //RENDERINGSTRATEGY_H

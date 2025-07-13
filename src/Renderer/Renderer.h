//
// Created by Carlo Baretta on 13/07/2025.
//

#ifndef RENDERINGSTRATEGY_H
#define RENDERINGSTRATEGY_H

typedef void (*InitializeFunction) (int xPos, int yPos, int width, int height);
typedef void (*RenderFunction) (void *context, float vertices[]);
typedef void (*SwapBuffersFunction) (void *context);


struct Renderer {
    //pointer to instance-specific data or "context"
    void *context;
    InitializeFunction initialize;
    RenderFunction render;
    SwapBuffersFunction swapBuffers;
};

//usage: swapRenderer(&currentRenderer, &newRenderer);
void swapRenderer(struct Renderer **current, const struct Renderer *new);

#endif //RENDERINGSTRATEGY_H

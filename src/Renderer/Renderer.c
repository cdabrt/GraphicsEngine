//
// Created by Carlo Baretta on 13/07/2025.
//

#include <RendererAPI/Renderer.h>
#include <stdlib.h>

/*
 **current is the actual renderer.
 *current is the pointer to the memory address of that renderer.
 current is the pointer to the address of *current.
 *new is the new renderer.
 new is the pointer to the new renderer.

 We free the memory address that *current points to (**current).
 We allocate new memory for a renderer, that *current points to.
 We copy the contents of *new into the newly allocated renderer (pointed to by *current).
*/
void swapRenderer(struct Renderer **current, const struct Renderer *new) {
    free(*current);
    *current = malloc(sizeof(struct Renderer));
    **current = *new;
}
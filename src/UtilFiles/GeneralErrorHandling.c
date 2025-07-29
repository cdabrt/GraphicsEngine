//
// Created by Carlo Baretta on 29/07/2025.
//

#include <stdio.h>
#include <stdlib.h>

void checkMalloc(void *mallocItem) {
    if (!mallocItem) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

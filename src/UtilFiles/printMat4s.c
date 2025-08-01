//
// Created by Carlo Baretta on 01/08/2025.
//

#include <cglm/struct.h>

void printMat4s(const mat4s matrix) {
    const int maxSizeOfMat4s = 4;

    printf("matrix:\n");
    for (int row = 0; row < maxSizeOfMat4s; ++row) {
        printf("[ ");
        for (int col = 0; col < maxSizeOfMat4s; ++col) {
            printf("%.3f ", matrix.raw[col][row]);  // column-major
        }
        printf("]\n");
    }
}
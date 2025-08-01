//
// Created by Carlo Baretta on 01/08/2025.
//

#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#include "cglm/struct/mat4.h"

struct Transformation {
    mat4s localTransformation;
    mat4s worldTransformation;
};

#endif //TRANSFORMATION_H

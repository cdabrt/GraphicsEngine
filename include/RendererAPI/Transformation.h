//
// Created by Carlo Baretta on 01/08/2025.
//

#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#include "cglm/struct/mat4.h"

/**
 * Transformation
 * Representation of the transformation of an object. This means: Position, rotation and scale.
 *
 * @param localTransformation the local transform.
 * @param worldTransformation the world transform.
 *
 * @note It is advised that the use of this struct and its use of @ref mat4s is abstracted away.
 * It is slightly easier to interface with separate position, rotation and scale values than to mess with a mat4s in
 * for instance an editor. Under the hood that data will have to be put into a mat4s (the engine does not do this,
 * this responsibility is yours).
 */
typedef struct Transformation {
    mat4s localTransformation;
    mat4s worldTransformation;
} Transformation;

#endif //TRANSFORMATION_H

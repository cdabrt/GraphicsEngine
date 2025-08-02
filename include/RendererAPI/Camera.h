//
// Created by Carlo Baretta on 01/08/2025.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "cglm/struct/mat4.h"
#include "RendererAPI/Transformation.h"

struct Camera {
    mat4s perspective;
    struct Transformation transformation;
    mat4s view;
    float fov;
    float frustumNear;
    float frustumFar;
};

#endif //CAMERA_H

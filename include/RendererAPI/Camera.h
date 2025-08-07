//
// Created by Carlo Baretta on 01/08/2025.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "cglm/struct/mat4.h"
#include "RendererAPI/Transformation.h"

typedef struct {
    mat4s perspective;
    mat4s view;
    Transformation transformation;
    float fov;
    float frustumNear;
    float frustumFar;
} Camera;

void updateCamera(Camera *camera);

#endif //CAMERA_H

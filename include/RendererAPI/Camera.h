//
// Created by Carlo Baretta on 01/08/2025.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "cglm/struct/mat4.h"
#include "RendererAPI/Transformation.h"

struct Camera {
    mat4s perspective;
    mat4s view;
    float speed;
    struct Transformation transformation;
    float fov;
    float frustumNear;
    float frustumFar;
};

void updateCamera(struct Camera *camera);

#endif //CAMERA_H

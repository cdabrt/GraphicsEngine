//
// Created by Carlo Baretta on 01/08/2025.
//

#ifndef CAMERA_H
#define CAMERA_H
#include <stdio.h>

#include "cglm/struct/mat4.h"
#include "Renderer/OpenGL/OpenGLHeaders.h"
#include "RendererAPI/Transformation.h"

typedef enum CameraBlockUniform {
    CAMERA_VIEW
} CameraUniform;

inline char *getBaseCameraBlockUniformString(const CameraUniform cameraUniforms)
{
    char *string = "\0";

    switch(cameraUniforms) {
        case CAMERA_VIEW: string = "CameraView"; break;
        default:
            perror("Unknown camera uniform");
    }

    return string;
}

inline unsigned int getBaseCameraBlockUniformBinding(const CameraUniform cameraUniforms)
{
    unsigned int uniformBinding = -1;

    switch(cameraUniforms) {
        case CAMERA_VIEW: uniformBinding = 1; break;
        default:
            perror("Unknown camera uniform");
    }

    return uniformBinding;
}

typedef struct CameraBlock {
    float view[16];
    float perspective[16];
} CameraBlock;

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

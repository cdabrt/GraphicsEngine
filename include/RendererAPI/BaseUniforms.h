//
// Created by carlo on 10-8-2025.
//

#ifndef BASEUNIFORMS_H
#define BASEUNIFORMS_H
#include <stdio.h>

typedef enum CameraBlockUniform {
    CAMERA_VIEW
} CameraUniform;

inline char *getBaseBlockUniformString(const CameraUniform cameraUniforms)
{
    char *string = "\0";

    switch(cameraUniforms) {
        case CAMERA_VIEW: string = "CameraView"; break;
        default:
            perror("Unknown camera uniform");
    }

    return string;
}

inline unsigned int getBaseBlockUniformBinding(const CameraUniform cameraUniforms)
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

#endif //BASEUNIFORMS_H

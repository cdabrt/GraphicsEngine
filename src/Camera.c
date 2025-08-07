//
// Created by Carlo Baretta on 03/08/2025.
//

#include "RendererAPI/Camera.h"
#include "cglm/struct/cam.h"


void updateCamera(Camera *camera) {
    vec4 *worldTransformationRaw = camera->transformation.worldTransformation.raw;

    const vec3s up = (vec3s){
        worldTransformationRaw[1][0],
        worldTransformationRaw[1][1],
        worldTransformationRaw[1][2]
    };

    const vec3s front = (vec3s){
        -worldTransformationRaw[2][0],
        -worldTransformationRaw[2][1],
        -worldTransformationRaw[2][2]
    };

    const vec3s position = (vec3s){
        worldTransformationRaw[3][0],
        worldTransformationRaw[3][1],
        worldTransformationRaw[3][2]
    };

    camera->view =
        glms_lookat(position, glms_vec3_add(position, front), up);
}

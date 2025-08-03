//
// Created by Carlo Baretta on 03/08/2025.
//

#include "RendererAPI/Camera.h"
#include "cglm/struct/cam.h"


void updateCamera(struct Camera *camera) {
    const float offset = 1.0f;
    const vec3s up = (vec3s){0.0f, 1.0f, 0.0f};
    const vec3s front = (vec3s){0.0f, 0.0f, offset};
    const vec3s position = (vec3s){
        camera->transformation.worldTransformation.raw[3][0],
        camera->transformation.worldTransformation.raw[3][1],
        camera->transformation.worldTransformation.raw[3][2]
    };
    camera->view =
        glms_lookat(position, glms_vec3_add(position, front), up);
}

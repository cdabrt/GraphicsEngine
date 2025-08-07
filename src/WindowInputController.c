//
// Created by Carlo Baretta on 13/07/2025.
//

#include <string.h>
#include "cglm/struct/affine-pre.h"
#include "cglm/struct/affine.h"
#include "cglm/struct/quat.h"
#include "Renderer/OpenGL/OpenGLHeaders.h"
#include "RendererAPI/Renderer.h"

void moveCamera(const Renderer *renderer, GLFWwindow *window);
void rotateCamera(const Renderer *renderer);

void processWindowInput(const Renderer *renderer) {
    GLFWwindow *window = renderer->context->window;
    moveCamera(renderer, window);
    rotateCamera(renderer);
}

void moveCamera(const Renderer *renderer, GLFWwindow *window) {
    Context *context = renderer->context;
    Camera *camera = renderer->context->camera;
    const float cameraSpeed = 2.5f;

    vec3s movement = GLMS_VEC3_ZERO;
    mat4s *transformation = &camera->transformation.worldTransformation;

    const vec3s forward = (vec3s){
        -transformation->raw[2][0],
        -transformation->raw[2][1],
        -transformation->raw[2][2]
    };

    const vec3s right = (vec3s){
        transformation->raw[0][0],
        transformation->raw[0][1],
        transformation->raw[0][2]
    };

    const vec3s up = (vec3s){
        transformation->raw[1][0],
        transformation->raw[1][1],
        transformation->raw[1][2]
    };

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        movement = glms_vec3_add(movement, forward);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        movement = glms_vec3_add(movement, glms_vec3_mul(forward, (vec3s){-1, -1, -1}));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        movement = glms_vec3_add(movement, glms_vec3_mul(right, (vec3s){-1, -1, -1}));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        movement = glms_vec3_add(movement, right);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        movement = glms_vec3_add(movement, up);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        movement = glms_vec3_add(movement, glms_vec3_mul(up, (vec3s){-1, -1, -1}));
    }

    if (!glms_vec3_eqv(movement, GLMS_VEC3_ZERO)) {
        movement = glms_vec3_normalize(movement);
        movement = glms_vec3_scale(movement, cameraSpeed * (float) context->deltaTime);

        *transformation = glms_translate(*transformation, movement);
    }
}


//TODO: MOVE AWAY FROM HERE
typedef struct PlayerControlledCamera {
    Transformation transform;
    float yaw;
    float pitch;
    bool firstFrame;
    double lastX, lastY;
} PlayerControlledCamera;

// PlayerControlledCamera *player = {
//     memset(0),
//     -90.0f,
//     0.0f,
//     true,
//     0,
//     0
// };
// const float sensitivity = 0.1f;

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    // if (player->firstFrame) {
    //     player->lastX = xPos;
    //     player->lastY = yPos;
    //     player->firstFrame = false;
    //     return;
    // }
    //
    // float xOffset = (float)(xPos - player->lastX);
    // float yOffset = (float)(player->lastY - yPos); // reversed because y-coord goes from top to bottom
    // player->lastX = xPos;
    // player->lastY = yPos;
    //
    // xOffset *= sensitivity;
    // yOffset *= sensitivity;
    //
    // player->yaw += xOffset;
    // player->pitch += yOffset;
    //
    // // Clamp pitch
    // if (player->pitch > 89.0f)  player->pitch = 89.0f;
    // if (player->pitch < -89.0f) player->pitch = -89.0f;
}


void rotateCamera(const Renderer *renderer) {
    const Camera *camera = renderer->context->camera;

    // Convert yaw/pitch to quaternion
    //glms_quat axisX = glms_quat_axis(glms_rad(pitch), (vec3s){1.0f, 0.0f, 0.0f});
    //quat axisY = glms_quat_axis(glms_rad(yaw),   (vec3s){0.0f, 1.0f, 0.0f});

    //glms_quat combined = glms_quat_mul(axisY, axisX);

    // Convert to mat4 and update camera's rotation matrix
    //mat4s rotMat = glms_quat_mat4(combined);
    //renderer->context->camera->transformation.worldTransformation = glms_mat4_mul(rotMat, camera->transformation.worldTransformation);
}
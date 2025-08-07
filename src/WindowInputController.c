//
// Created by Carlo Baretta on 13/07/2025.
//

#include <string.h>

#include "MouseInputState.h"
#include "cglm/struct/affine-pre.h"
#include "cglm/struct/affine.h"
#include "cglm/struct/quat.h"
#include "Renderer/OpenGL/OpenGLHeaders.h"
#include "RendererAPI/Renderer.h"

void moveCamera(const Renderer *renderer, GLFWwindow *window);
void rotateCamera(const Renderer *renderer, GLFWwindow *window);

void processWindowInput(const Renderer *renderer) {
    GLFWwindow *window = renderer->context->window;
    moveCamera(renderer, window);
    rotateCamera(renderer, window);
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

    const vec3s inverse = (vec3s){-1, -1, -1};

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        movement = glms_vec3_add(movement, forward);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        movement = glms_vec3_add(movement, glms_vec3_mul(forward, inverse));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        movement = glms_vec3_add(movement, right);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        movement = glms_vec3_add(movement, glms_vec3_mul(right, inverse));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        movement = glms_vec3_add(movement, up);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        movement = glms_vec3_add(movement, glms_vec3_mul(up, inverse));
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

void mouseCallback(GLFWwindow* window, const double xPos, const double yPos) {
    MouseInputState *state = glfwGetWindowUserPointer(window);
    if (!state) return;
    if (state->lookDisabled) return;

    if (state->firstFrame) {
        state->lastX = xPos;
        state->lastY = yPos;
        state->firstFrame = false;
        return;
    }

    float xOffset = (float)(xPos - state->lastX);
    float yOffset = (float)(yPos - state->lastY);
    state->lastX = xPos;
    state->lastY = yPos;

    if (xOffset == 0.0f && yOffset == 0.0f) {
        state->rotationChanged = false;
        return;
    }
    state->rotationChanged = true;

    state->yaw += xOffset;
    state->pitch += yOffset;

    // Clamp pitch
    if (state->pitch > 89.0f)  state->pitch = 89.0f;
    if (state->pitch < -89.0f) state->pitch = -89.0f;
}


void rotateCamera(const Renderer *renderer, GLFWwindow *window) {
    Context *context = renderer->context;
    Camera *camera = context->camera;
    MouseInputState *state = glfwGetWindowUserPointer(window);
    if (!state) return;
    if (!state->rotationChanged) return;

    const float yaw = state->yaw * state->sensitivity * (float)renderer->context->deltaTime;
    const float pitch = state->pitch * state->sensitivity * (float)renderer->context->deltaTime;

    const versors pitchQuaternion = glms_quatv(glm_rad(pitch), (vec3s){1.0f, 0.0f, 0.0f});
    const versors yawQuaternion = glms_quatv(glm_rad(yaw),   (vec3s){0.0f, 1.0f, 0.0f});
    const versors rotationQuaternion = glms_quat_mul(pitchQuaternion, yawQuaternion);
    const mat4s rotationMatrix = glms_quat_mat4(rotationQuaternion);

    state->yaw = 0.0f;
    state->pitch = 0.0f;

    const vec3s position = {
        camera->transformation.worldTransformation.raw[3][0],
        camera->transformation.worldTransformation.raw[3][1],
        camera->transformation.worldTransformation.raw[3][2]
    };

    camera->transformation.worldTransformation =
        camera->transformation.worldTransformation = glms_translate(rotationMatrix, position);

    state->rotationChanged = false;
}

void exitLook(GLFWwindow* window, int key, int action) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        MouseInputState *state = glfwGetWindowUserPointer(window);
        state->firstFrame = true;
        state->lookDisabled = !state->lookDisabled;

        if (state->lookDisabled) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
}

void enterLook(GLFWwindow* window, int key, int action) {
    if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        MouseInputState *state = glfwGetWindowUserPointer(window);
        state->firstFrame = true;
        state->lookDisabled = false;

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

//For actions that should take place only once, when a key is pressed.
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    exitLook(window, key, action);
}

void mousePressCallback(GLFWwindow* window, int key, int action, int mods) {
    enterLook(window, key, action);
}
//
// Created by Carlo Baretta on 13/07/2025.
//

#include "cglm/struct/affine-pre.h"
#include "Renderer/OpenGL/OpenGLHeaders.h"
#include "RendererAPI/Renderer.h"

void processWindowInput(const struct Renderer *renderer) {
    GLFWwindow* window = renderer->context->window;
    struct Context *context = renderer->context;
    struct Camera *camera = renderer->context->camera;


    vec3s movement = GLMS_VEC3_ZERO;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        movement = glms_vec3_add(movement, (vec3s){
            camera->transformation.worldTransformation.raw[2][0],
            camera->transformation.worldTransformation.raw[2][1],
            camera->transformation.worldTransformation.raw[2][2]
        });
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        movement = glms_vec3_add(movement, (vec3s){
            -camera->transformation.worldTransformation.raw[2][0],
            -camera->transformation.worldTransformation.raw[2][1],
            -camera->transformation.worldTransformation.raw[2][2]
        });
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        movement = glms_vec3_add(movement, (vec3s){
            camera->transformation.worldTransformation.raw[0][0],
            camera->transformation.worldTransformation.raw[0][1],
            camera->transformation.worldTransformation.raw[0][2]
        });
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        movement = glms_vec3_add(movement, (vec3s){
            -camera->transformation.worldTransformation.raw[0][0],
            -camera->transformation.worldTransformation.raw[0][1],
            -camera->transformation.worldTransformation.raw[0][2]
        });
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        movement = glms_vec3_add(movement, (vec3s){
            camera->transformation.worldTransformation.raw[1][0],
            camera->transformation.worldTransformation.raw[1][1],
            camera->transformation.worldTransformation.raw[1][2]
        });
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        movement = glms_vec3_add(movement, (vec3s){
            -camera->transformation.worldTransformation.raw[1][0],
            -camera->transformation.worldTransformation.raw[1][1],
            -camera->transformation.worldTransformation.raw[1][2]
        });
    }

    if (!glms_vec3_eqv(movement, GLMS_VEC3_ZERO)) {
        movement = glms_vec3_normalize(movement);
        camera->transformation.worldTransformation = glms_translate(
            camera->transformation.worldTransformation,
            glms_vec3_scale(movement, camera->speed * (float) context->deltaTime)
        );
    }
}

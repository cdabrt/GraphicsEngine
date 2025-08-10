//
// Created by Carlo Baretta on 10/07/2025.
//

#include <stdio.h>
#include <string.h>
#include <Window.h>
#include <WindowInputController.h>
#include <RendererAPI/Renderer.h>
#include <RendererAPI/RawMesh.h>
#include <RendererAPI/RendererFactory.h>
#include "cglm/struct/affine-pre.h"
#include "cglm/struct/affine.h"
#include "cglm/struct/cam.h"
#include "Renderer/OpenGL/OpenGLHeaders.h"
#include "RendererAPI/Model.h"
#include "UtilFiles/Macros.h"
#include "RendererAPI/Context.h"
#include "../include/RendererAPI/Camera.h"
#include "RendererAPI/Texture.h"
#include "MouseInputState.h"

/*
    TODO: When the Graphics Engine is turned into a library or framework of some sorts, subsequent projects
          would need a main function like this. Anything within the src folder that does not reside within
          the "Renderer" or "UtilFiles" folders, need to be moved to a different project
          (a separate editor or perhaps game engine will be made with this project).
*/

Renderer *setupProgram(const int width, const int height, const int xPos, const int yPos, bool drawWireframe,
    const float FOV, const float frustumNear, const float frustumFar) {
    const float orthographicFrustumSizeFactor = 1000;
    glfwWindowSetup();
    GLFWwindow* window = createWindow(width, height);

    //Ignore warning, mouseState is freed.
    MouseInputState *mouseState = malloc(sizeof(MouseInputState));
    *mouseState = (MouseInputState) {
        .lastX = 400.0f,  // center of your window maybe
        .lastY = 300.0f,
        .yaw = -90.0f,
        .pitch = 0.0f,
        .firstFrame = true,
        .sensitivity = 3.0f,
        .rotationChanged = false,
        .lookDisabled = true,
    };
    glfwSetWindowUserPointer(window, mouseState);

    Renderer *renderer = createRenderer(window, OPENGL);
    Context *context = renderer->context;
    Camera *camera = context->camera;

    camera->perspective = glms_perspective(glm_rad(FOV), (float)width/(float)height, frustumNear, frustumFar);
    //Uncomment for orthographic perspective. Note, you can also change perspective at run-time.
    //camera->perspective = glms_ortho(-(float)width/orthographicFrustumSizeFactor, (float)width/orthographicFrustumSizeFactor, -(float)height/orthographicFrustumSizeFactor, (float)height/orthographicFrustumSizeFactor, frustumNear, frustumFar);
    camera->transformation.worldTransformation = glms_translate(glms_mat4_identity(), (vec3s){0.0f, 0.0f, 3.0f});
    camera->fov = FOV;
    camera->frustumNear = frustumNear;
    camera->frustumFar = frustumFar;

    renderer->context->drawWireframe = drawWireframe;
    //The base shader should always be set up before any Model, VBO and EBO setup
    renderer->prepareRenderer(context, xPos, yPos, width, height);

    return renderer;
}

//TODO: REMOVE, FOR TESTING ONLY
void testProgram(Renderer *renderer) {
    Context *context = renderer->context;
    RendererInjector *rendererInjector = renderer->injector;

    //Vertices are constructed as follows:
    //x, y, z; r, g, b
    const float vertices[] = {
        //Positions          //Colours          //Texture coordinates
        //Front
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f, //0
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f, //1
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f, //2
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f, //3
        //Back
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f, //4
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f, //5
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f, //6
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f, //7
        //Left
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, //8
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f, //9
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f, //10
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f, //11
        //Right
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,   1.0f, 0.0f, //12
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 0.0f, //13
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f, //14
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,   1.0f, 1.0f, //15
        //Top
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   0.0f, 0.0f, //16
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   1.0f, 0.0f, //17
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,   1.0f, 1.0f, //18
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,   0.0f, 1.0f, //19
        //Bottom
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,   1.0f, 1.0f, //20
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,   0.0f, 1.0f, //21
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,   0.0f, 0.0f, //22
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,   1.0f, 0.0f, //23
    };

    const unsigned int indices[] = {
        //Front
        0, 1, 2,
        2, 3, 0,

        //Back
        4, 6, 5,
        6, 4, 7,

        //Left
        9, 10, 8,
        11, 8, 10,

        //Right
        12, 14, 13,
        15, 14, 12,

        //Top
        16, 17, 18,
        18, 19, 16,

        //Bottom
        22, 21, 20,
        20, 23, 22
    };


    Texture textures[] = {
        {
            strdup("../src/Textures/House.png"),
            DIFFUSE,
            getBaseTextureTypeUniformString(DIFFUSE),
            //The id and textureUnit are handled under the hood.
            0,
            0
        }
    };

    RawMesh mesh = {
        vertices,
        indices,
        sizeof(vertices),
        sizeof(indices),
        textures,
        sizeof(textures) / sizeof(textures[0]),
        };

    //For testing:

    //Confirms switching models and using different associated shaders works.
    //To create and register a shader program:
    // unsigned int shaderProgram = rendererInjector->registerShaderProgram(
    //     "../src/Renderer/OpenGL/Shaders/Vertex/vertex_wireframe.vert",
    //     "\0",
    //     "../src/Renderer/OpenGL/Shaders/Fragment/fragment_wireframe.frag"
    //     );
    // registerShaderProgram(openGLContext, shaderProgram, WIREFRAME_SHADER);
    //Set to WIREFRAME_SHADER for testing
    const unsigned int id = rendererInjector->getShaderProgramID(context, getBaseShaderString(BASE_SHADER));
    rendererInjector->registerMesh(context, &mesh, "FirstMesh", id);

    //Apply some transformations
    Model *model = rendererInjector->getModel(context, rendererInjector->getModelID(context, "FirstMesh"));
    //model->transformation.localTransformation = glms_rotate(model->transformation.localTransformation, glm_rad(-55.0f), (vec3s){ .x = 1.0f, .y = 0.0f, .z = 0.0f });
    //model->transformation.localTransformation = glms_scale(model->transformation.localTransformation , (vec3s){ .x = 1.0f, .y = 1.0f, .z = 1.0f});
    model->transformation.worldTransformation = glms_translate(model->transformation.worldTransformation, (vec3s){0.0f, 0.0f, 1.0f});
}

void loopProgram(const Renderer *renderer) {
    Context *context = renderer->context;
    GLFWwindow* window = renderer->context->window;

    while (!glfwWindowShouldClose(window)) {
        //Needs to be set only once every frame
        context->deltaTime = glfwGetTime() - context->deltaTime;

        processWindowInput(renderer);

        //TODO: Inject movement into the render loop
        //----------------
        //Testing:
        Model *model = renderer->injector->getModel(context, renderer->injector->getModelID(context, "FirstMesh"));
        model->transformation.worldTransformation = glms_rotate(
            model->transformation.worldTransformation,
            (float) context->deltaTime * glm_rad(50.0f),
            (vec3s){ .x = 1.0f, .y = 1.0f, .z = 1.0f }
            );
        context->deltaTime = glfwGetTime();
        //----------------

        updateCamera(renderer->context->camera);
        renderer->render(context);

        renderer->swapBuffers(renderer->context);
    }
}

void killProgram(Renderer *renderer) {
    renderer->kill(renderer);
    free(glfwGetWindowUserPointer(renderer->context->window));
}

int main() {
    const int width = 800;
    const int height = 600;
    const int xPos = 0;
    const int yPos = 0;
    const bool drawWireframe = false;
    const float FOV = 70;
    const float frustumNear = 0.1f;
    const float frustumFar = 100.0f;

    Renderer *renderer = setupProgram(width, height, xPos, yPos, drawWireframe, FOV, frustumNear, frustumFar);

    testProgram(renderer);

    loopProgram(renderer);

    killProgram(renderer);

    return EXIT_SUCCESS;
}

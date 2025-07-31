//
// Created by Carlo Baretta on 10/07/2025.
//

#include <stdio.h>
#include <string.h>
#include <Window.h>
#include <WindowInputController.h>
#include <../include/RendererAPI/Renderer.h>
#include <../include/RendererAPI/RawMesh.h>
#include <../include/RendererAPI/RendererFactory.h>
#include "cglm/struct/affine-pre.h"
#include "cglm/struct/affine.h"
#include "Renderer/OpenGL/OpenGLHeaders.h"
#include "RendererAPI/Model.h"
#include "UtilFiles/MacrosAndUniforms.h"

/*
    When the Graphics Engine is turned into a library or framework of some sorts,
    subsequent projects would need a main function like this.
    I am planning on making a game engine. The main loop should be injectable.
    Every script should have an init and loop function. In the loop in the main all scripts are loaded
    and their loop functions are ran. Same goes for the init functions of all the files in the main initialization
*/
void killProgram(struct Renderer *renderer, struct RendererInjector *rendererInjector) {
    renderer->kill(renderer->context);
    free(renderer);
    free(rendererInjector);
}

void programLoop(struct Context *context, const struct Renderer *renderer, const bool drawWireframe) {
    GLFWwindow* window = renderer->context->window;
    //Main window render loop.
    while (!glfwWindowShouldClose(window)) {
        //Input processing
        processWindowInput(window);

        //Rendering pipeline
        renderer->render(context, drawWireframe);

        renderer->swapBuffers(renderer->context);
    }
}

int main() {
    const int width = 800;
    const int height = 600;
    const int xPos = 0;
    const int yPos = 0;
    const bool drawWireframe = false;

    glfwWindowSetup();
    GLFWwindow* window = createWindow(width, height);

    struct Renderer *renderer = createRenderer(window, OPENGL);
    struct RendererInjector *rendererInjector = createRendererInjector(OPENGL);

    void *context = renderer->context;
    //The base shader should always be set up before any Model, VBO and EBO setup
    renderer->initialize(context, xPos, yPos, width, height);

    //TODO: REMOVE, FOR TESTING ONLY
    //Vertices are constructed as follows:
    //x, y, z; r, g, b
    const float vertices[] = {
        //Positions         //Colours           //Texture coordinates
        -0.5f,  0.5f, 0.0f,  0.8f, 0.5f, 0.2f,   0.0f, 1.0f,
        0.5f,  0.5f, 0.0f,  0.8f, 0.5f, 0.2f,   1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
   };

    const unsigned int indices[] = {
        2, 3, 0,
        3, 1, 0,
    };

    struct Texture textures[] = {
        {
            strdup("../src/Renderer/OpenGL/Textures/House.png"),
            DIFFUSE,
            getBaseTextureTypeUniformString(DIFFUSE),
            //The id and textureUnit are handled under the hood.
            0,
            0
        }
    };

    struct RawMesh mesh = {
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
    // unsigned int shaderProgram = rendererInjector->createShaderProgram(
    //     "../src/Renderer/OpenGL/Shaders/Vertex/vertex_wireframe.vert",
    //     "\0",
    //     "../src/Renderer/OpenGL/Shaders/Fragment/fragment_wireframe.frag"
    //     );
    // registerShaderProgram(openGLContext, shaderProgram, WIREFRAME_SHADER);
    //Set to WIREFRAME_SHADER for testing
    const unsigned int id = rendererInjector->getShaderProgramID(context, getBaseShaderUniformString(BASE_SHADER));
    rendererInjector->registerMesh(context, &mesh, "FirstMesh", id);

    //Apply some transformations
    const struct Model *model = rendererInjector->getModel(context, rendererInjector->getModelID(context, "FirstMesh"));
    //printf("%.6f", model->localTransformation->col->x);

    *model->localTransformation = glms_rotate(*model->localTransformation, glm_rad(90.0f), (vec3s){ .x = 0.0f, .y = 0.0f, .z = 1.0f });
    *model->localTransformation  = glms_scale(*model->localTransformation , (vec3s){ .x = 0.5f, .y = 0.5f, .z = 0.5f});

    /*
      Shader injection should happen before this call, so that the wireframe shaders
      are always used when drawWireframe is true.
    */
    renderer->prepareRenderer(context, drawWireframe);

    programLoop(context, renderer, drawWireframe);

    /*
     TODO: Perhaps this should be a Windows and Linux only thing. In Mac if you press the "x",
        it does not fully quit a program, just hides it in the background.
        Maybe do not terminate the while loop on macOS.
    */

    killProgram(renderer, rendererInjector);

    return EXIT_SUCCESS;
}

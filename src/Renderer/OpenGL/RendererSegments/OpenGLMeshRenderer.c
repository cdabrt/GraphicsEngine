//
// Created by Carlo Baretta on 01/08/2025.
//

#include "../OpenGLRenderer.h"
#include "../Context/OpenGLContext.h"
#include "../ErrorHandling/OpenGLErrorHandling.h"
#include "../../../UtilFiles/Macros.h"
#include "../OpenGLHeaders.h"
#include "OpenGLTextureRenderer.h"
#include "cglm/struct.h"
#include "RendererAPI/Context.h"

void setTransformUniforms(const Context *context, const Model *model, const unsigned int activeShaderProgram) {
    const Transformation transformation = model->transformation;
    const Camera *camera = context->camera;

    const unsigned int transformUniform = glGetUniformLocation(activeShaderProgram, getBaseMeshUniformString(TRANSFORM));
    checkUniformLocation(transformUniform);
    const unsigned int projectionUniform = glGetUniformLocation(activeShaderProgram, getBaseMeshUniformString(PROJECTION));
    checkUniformLocation(projectionUniform);
    const unsigned int viewUniform = glGetUniformLocation(activeShaderProgram, getBaseMeshUniformString(VIEW));
    checkUniformLocation(viewUniform);

    //TODO: Do not just use local transform. Use world transform as well.
    const mat4s modelTransformation = glms_mat4_mul(
        transformation.localTransformation,
        transformation.worldTransformation
        );
    glUniformMatrix4fv(
            (GLint)transformUniform,
            1,
            GL_FALSE,
            modelTransformation.raw
        );

    glUniformMatrix4fv(
        (GLint)projectionUniform,
        1,
        GL_FALSE,
        camera->perspective.raw
    );

    glUniformMatrix4fv(
        (GLint)viewUniform,
        1,
        GL_FALSE,
        camera->view.raw
    );
}

void killMeshes(OpenGLContext *openGLContext) {
    const int numberOfmodels = 1;
    for (size_t i = 0; i < openGLContext->modelCount; i++) {
        Model *model = &openGLContext->models[i];
        killTextures(model);
        glDeleteVertexArrays(numberOfmodels, &model->id);
    }

    openGLContext->modelCount = 0;
    free(openGLContext->models);
    CHECK_OPENGL_ERRORS;
}
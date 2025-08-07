//
// Created by Carlo Baretta on 01/08/2025.
//

#include <string.h>

#include "../OpenGLRenderer.h"
#include "../Context/OpenGLContext.h"
#include "../ErrorHandling/OpenGLErrorHandling.h"
#include "../OpenGLHeaders.h"
#include "OpenGLTextureRenderer.h"
#include "cglm/struct.h"

void setTransformUniforms(const Model *model, const unsigned int activeShaderProgram) {
    const Transformation transformation = model->transformation;

    const GLuint transformUniform = glGetUniformLocation(activeShaderProgram, getBaseMeshUniformString(TRANSFORM));
    checkUniformLocation(transformUniform);

    //TODO: Allow ShaderProgram to have a list of uniforms as well, exact same as UBO.
    //TODO: Check if this multiplication is the correct way
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
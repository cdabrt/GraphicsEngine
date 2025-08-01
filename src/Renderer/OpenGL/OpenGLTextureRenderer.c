//
// Created by Carlo Baretta on 01/08/2025.
//

#include "OpenGLRenderer.h"
#include "Context/OpenGLContext.h"
#include "ErrorHandling/OpenGLErrorHandling.h"
#include "Injector/OpenGLInjector.h"
#include "OpenGLHeaders.h"

void bindTextures(const struct Model *model, const GLuint activeShaderProgram) {
    for (int i = 0; i < model->textureCount; i++) {
        const struct Texture *texture = &model->textures[i];
        glActiveTexture(GL_TEXTURE0 + texture->textureUnit);
        glBindTexture(GL_TEXTURE_2D, texture->id);
        GLint uniformLocation = glGetUniformLocation(activeShaderProgram, texture->uniformName);
        checkUniformLocation(uniformLocation);
        glUniform1i(uniformLocation, texture->textureUnit);
    }
    CHECK_OPENGL_ERRORS;
}



void cleanUpRenderer(const struct Model *model) {
    //Unbind textures
    for (int i = 0; i < model->textureCount; i++) {
        const struct Texture *texture = &model->textures[i];
        glActiveTexture(GL_TEXTURE0 + texture->textureUnit);
        //Texture 0 = "No texture"
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    CHECK_OPENGL_ERRORS;
}

void killTextures(struct Model *model) {
    const int numberOfTexturesToDelete = 1;
    for (int i = 0; i < model->textureCount; i++) {
        struct Texture *texture = &model->textures[i];
        glDeleteTextures(numberOfTexturesToDelete, &texture->id);
        free(texture->path);
        texture->path = "";
    }

    model->textureCount = 0;
    free(model->textures);
    CHECK_OPENGL_ERRORS;
}
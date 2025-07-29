//
// Created by Carlo Baretta on 20/07/2025.
//

#include "../include/RendererAPI/RawMesh.h"
#include "Renderer/OpenGL/OpenGLContext.h"
#include <stb_image.h>
#include <string.h>
#include "Renderer/OpenGL/OpenGLErrorHandling.h"
#include "Renderer/OpenGL/OpenGLHeaders.h"
#include "Renderer/OpenGL/Injector/OpenGLInjector.h"
#include "UtilFiles/MacrosAndUniforms.h"



void setTextureParameters() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    CHECK_OPENGL_ERRORS;
}

void generateTexture(struct Texture *texture, const GLuint textureID, const int textureUnit, const int nrChannels,
    const int width, const int height, const unsigned char *data) {
    const int border = 0;
    const int level = 0;

    GLint format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, level, GL_RGB, width, height, border,
                format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    texture->id = textureID;
    texture->textureUnit = textureUnit;

    CHECK_OPENGL_ERRORS;
}

void registerFileNotFoundImage(struct OpenGLContext *context, struct Model *model) {
    const char *fileNotFoundPath = strdup("../src/Renderer/OpenGL/Textures/FileNotFound.png");
    const int numberOfRegistersAtTime = 1;
    int width, height, nrChannels;
    const int desiredChannels = 0;
    GLuint textureID;

    glGenTextures(numberOfRegistersAtTime, &textureID);
    setTextureParameters();

    unsigned char *data = stbi_load(fileNotFoundPath, &width, &height, &nrChannels, desiredChannels);
    free(fileNotFoundPath);

    struct Texture texture = {
        (char *) fileNotFoundPath,
        DIFFUSE,
        getBaseTextureTypeUniformString(DIFFUSE),
        textureID,
        GL_TEXTURE0
    };

    generateTexture(&texture, textureID, 1, nrChannels, width, height, data);
    registerTexture(context, model, texture);
    stbi_image_free(data);
}

void openGLRegisterTextures(struct OpenGLContext *context, const struct Texture *textures, const size_t textureCount,
    struct Model *model) {
    const int numberOfRegistersAtTime = 1;
    int width, height, nrChannels;
    const int desiredChannels = 0;

    if (textureCount == 0) {
        registerFileNotFoundImage(context, model);
    } else {
        for (int i = 0; i < textureCount; i++) {
            struct Texture texture = textures[i];

            GLuint textureID;
            glGenTextures(numberOfRegistersAtTime, &textureID);
            setTextureParameters();

            stbi_set_flip_vertically_on_load(1);
            unsigned char *data = stbi_load(texture.path, &width, &height, &nrChannels, desiredChannels);

            if (data) {
                generateTexture(&texture, textureID, i + 1, nrChannels, width, height, data);
                registerTexture(context, model, texture);
            }
            else {
                stbi_image_free(data);
                registerFileNotFoundImage(context, model);
                fprintf(stderr, "Failed to load texture: %s\n", stbi_failure_reason());
                return;
            }
            stbi_image_free(data);
        }
    }
}